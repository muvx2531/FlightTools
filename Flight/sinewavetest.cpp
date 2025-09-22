#include "SineWaveTest.h"
#include <QDebug>
#include <QVariantList>
#include <QtMath>
#include <algorithm>

// SineWaveWorker Implementation
SineWaveWorker::SineWaveWorker(RingBuffer<SampleData, 65536>* buffer, QObject* parent)
    : QObject(parent)
    , m_buffer(buffer)
    , m_timer(new QTimer(this))
    , m_sampleCounter(0)
    , m_running(false)
    , m_rng(std::random_device{}())
    , m_noiseDist(0.0, 1.0)
{
    // High-precision timer for sample generation
    m_timer->setTimerType(Qt::PreciseTimer);
    connect(m_timer, &QTimer::timeout, this, &SineWaveWorker::generateSamples);
    
    // Initialize with default parameters
    GeneratorParams defaultParams;
    setParams(defaultParams);
    
    qDebug() << "SineWaveWorker: Initialized with" << SAMPLES_PER_BATCH << "samples/batch";
}

void SineWaveWorker::setParams(const GeneratorParams& params)
{
    QMutexLocker locker(&m_paramsMutex);
    m_params = params;
    
    // Update timer interval based on sample rate
    // Generate SAMPLES_PER_BATCH samples per timer event
    int intervalMs = static_cast<int>(1000.0 * SAMPLES_PER_BATCH / params.sampleRate);
    intervalMs = std::max(1, intervalMs);  // Minimum 1ms
    m_timer->setInterval(intervalMs);
    
    qDebug() << "SineWaveWorker: Parameters updated - Sample rate:" << params.sampleRate 
             << "Hz, Timer interval:" << intervalMs << "ms";
}

GeneratorParams SineWaveWorker::getParams() const
{
    QMutexLocker locker(&m_paramsMutex);
    return m_params;
}

void SineWaveWorker::start()
{
    if (!m_running) {
        m_running = true;
        m_sampleCounter = 0;
        m_elapsedTimer.start();
        m_timer->start();
        
        qDebug() << "SineWaveWorker: Started data generation";
    }
}

void SineWaveWorker::stop()
{
    if (m_running) {
        m_running = false;
        m_timer->stop();
        
        qDebug() << "SineWaveWorker: Stopped data generation";
    }
}

void SineWaveWorker::reconfigure(const GeneratorParams& params)
{
    setParams(params);
}

void SineWaveWorker::generateSamples()
{
    if (!m_running || !m_buffer) return;
    
    GeneratorParams params;
    {
        QMutexLocker locker(&m_paramsMutex);
        params = m_params;
    }
    
    // Generate batch of samples
    for (int i = 0; i < SAMPLES_PER_BATCH; ++i) {
        // Deterministic timestamp: t = k/Fs
        double t = static_cast<double>(m_sampleCounter) / params.sampleRate;
        
        SampleData sample;
        sample.t = t;
        
        // Generate 4 channels: dc + amp*sin(2π f t + phase) + noise
        for (int ch = 0; ch < 4; ++ch) {
            double phaseRad = params.phase[ch] * M_PI / 180.0;  // Convert degrees to radians
            double sineValue = params.amplitude[ch] * std::sin(2.0 * M_PI * params.frequency[ch] * t + phaseRad);
            double noise = params.noiseLevel[ch] * m_noiseDist(m_rng);
            
            float channelValue = static_cast<float>(params.dc[ch] + sineValue + noise);
            
            switch (ch) {
                case 0: sample.y0 = channelValue; break;
                case 1: sample.y1 = channelValue; break;
                case 2: sample.y2 = channelValue; break;
                case 3: sample.y3 = channelValue; break;
            }
        }
        
        // Force push to ring buffer (never blocks producer)
        m_buffer->force_push(sample);
        m_sampleCounter++;
    }
    
    // Debug output every 1000 batches (less frequent)
    static int batchCount = 0;
    if (++batchCount % 1000 == 0) {
        double bufferUsage = m_buffer->usage() * 100.0;
        qDebug() << "SineWaveWorker: Generated" << m_sampleCounter << "samples, buffer usage:" 
                 << QString::number(bufferUsage, 'f', 1) << "%";
    }
}

// SineWaveTest Implementation
SineWaveTest::SineWaveTest(QObject* parent)
    : QObject(parent)
    , m_worker(nullptr)
    , m_workerThread(nullptr)
    , m_flushTimer(new QTimer(this))
    , m_running(false)
{
    // Thread and worker will be created on demand in start()
    
    // Setup UI flush timer (30 Hz)
    m_flushTimer->setTimerType(Qt::CoarseTimer);
    m_flushTimer->setInterval(static_cast<int>(1000.0 / UI_UPDATE_RATE));
    connect(m_flushTimer, &QTimer::timeout, this, &SineWaveTest::updateBufferUsage);
    
    qDebug() << "SineWaveTest: Initialized with buffer capacity:" << m_buffer.capacity() 
             << "UI update rate:" << UI_UPDATE_RATE << "Hz";
}

SineWaveTest::~SineWaveTest()
{
    stop();
    
    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait(3000);  // Wait up to 3 seconds
        if (m_workerThread->isRunning()) {
            m_workerThread->terminate();
            m_workerThread->wait(1000);
        }
    }
}

double SineWaveTest::sampleRate() const
{
    if (m_worker) {
        return m_worker->getParams().sampleRate;
    }
    return 1000.0;  // Default when no worker exists
}

int SineWaveTest::bufferUsage() const
{
    return static_cast<int>(m_buffer.usage() * 100.0);
}

void SineWaveTest::start()
{
    start(QVariantMap());  // Start with default parameters
}

void SineWaveTest::start(const QVariantMap& params)
{
    QMutexLocker locker(&m_mutex);
    
    if (!m_running) {
        // Clean up any existing thread/worker first
        if (m_workerThread) {
            if (m_workerThread->isRunning()) {
                qDebug() << "SineWaveTest: Warning - thread still running, waiting for stop...";
                m_workerThread->quit();
                m_workerThread->wait(3000);
            }
            // Delete the old thread and worker
            m_workerThread->deleteLater();
            m_worker = nullptr; // Worker will be deleted by thread cleanup
        }
        
        // Create new thread and worker for restart
        m_workerThread = new QThread(this);
        m_worker = new SineWaveWorker(&m_buffer);
        m_worker->moveToThread(m_workerThread);
        
        // Reconnect thread lifecycle signals
        connect(m_workerThread, &QThread::started, m_worker, &SineWaveWorker::start);
        connect(m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);
        
        // Configure parameters if provided
        if (!params.isEmpty()) {
            GeneratorParams genParams = variantMapToParams(params);
            m_worker->setParams(genParams);
        }
        
        m_running = true;
        
        // Clear buffer before starting
        m_buffer.clear();
        
        m_workerThread->start();
        m_flushTimer->start();
        
        emit runningChanged(true);
        emit sampleRateChanged(sampleRate());
        
        qDebug() << "SineWaveTest: Started with sample rate:" << sampleRate() << "Hz";
    } else {
        qDebug() << "SineWaveTest: Already running, ignoring start request";
    }
}

void SineWaveTest::stop()
{
    QMutexLocker locker(&m_mutex);
    
    if (m_running) {
        m_running = false;
        m_flushTimer->stop();
        
        // Stop the worker first
        if (m_worker) {
            QMetaObject::invokeMethod(m_worker, "stop", Qt::BlockingQueuedConnection);
        }
        
        // Then stop the thread gracefully
        if (m_workerThread && m_workerThread->isRunning()) {
            m_workerThread->quit();
            if (!m_workerThread->wait(3000)) {  // Wait up to 3 seconds
                qWarning() << "SineWaveTest: Thread did not stop gracefully, terminating...";
                m_workerThread->terminate();
                m_workerThread->wait(1000);
            }
        }
        
        emit runningChanged(false);
        
        qDebug() << "SineWaveTest: Stopped";
    } else {
        qDebug() << "SineWaveTest: Already stopped, ignoring stop request";
    }
}

void SineWaveTest::reconfigure(const QVariantMap& params)
{
    if (m_worker && !params.isEmpty()) {
        GeneratorParams genParams = variantMapToParams(params);
        QMetaObject::invokeMethod(m_worker, "reconfigure", Qt::QueuedConnection, 
                                Q_ARG(GeneratorParams, genParams));
        
        emit sampleRateChanged(sampleRate());
        
        qDebug() << "SineWaveTest: Reconfigured with new parameters";
    }
}

void SineWaveTest::setSampleRate(double rate)
{
    if (rate > 0 && rate != sampleRate()) {
        QVariantMap params;
        params["sampleRate"] = rate;
        reconfigure(params);
    }
}

void SineWaveTest::flushToQml(QObject* qmlOscilloscope)
{
    if (!qmlOscilloscope) return;
    
    // Pop up to MAX_BATCH_SIZE samples from ring buffer
    SampleData samples[MAX_BATCH_SIZE];
    size_t sampleCount = m_buffer.pop_batch(samples, MAX_BATCH_SIZE);
    
    if (sampleCount == 0) return;
    
    // Calculate decimation stride for ~150 points/sec/channel display rate
    double currentSampleRate = sampleRate();
    int stride = static_cast<int>(std::ceil(currentSampleRate / DEFAULT_DISPLAY_RATE));
    stride = std::max(1, stride);
    
    // Prepare decimated data for QML
    QVariantList timestamps, ch0, ch1, ch2, ch3;
    
    for (size_t i = 0; i < sampleCount; i += stride) {
        const SampleData& sample = samples[i];
        
        timestamps.append(sample.t);
        ch0.append(sample.y0);
        ch1.append(sample.y1);
        ch2.append(sample.y2);
        ch3.append(sample.y3);
    }
    
    if (!timestamps.isEmpty()) {
        // Call QML method to add samples
        QMetaObject::invokeMethod(qmlOscilloscope, "addSamples",
                                Q_ARG(QVariant, QVariant::fromValue(timestamps)),
                                Q_ARG(QVariant, QVariant::fromValue(ch0)),
                                Q_ARG(QVariant, QVariant::fromValue(ch1)),
                                Q_ARG(QVariant, QVariant::fromValue(ch2)),
                                Q_ARG(QVariant, QVariant::fromValue(ch3)));
        
        // Debug output (less frequent)
        static int flushCount = 0;
        if (++flushCount % 30 == 0) {  // Every second at 30 Hz
            qDebug() << "SineWaveTest: Flushed" << timestamps.size() << "points to QML"
                     << "(stride=" << stride << ", buffer usage=" << bufferUsage() << "%)";
        }
    }
}

GeneratorParams SineWaveTest::variantMapToParams(const QVariantMap& map) const
{
    GeneratorParams params;
    
    if (map.contains("sampleRate"))
        params.sampleRate = map["sampleRate"].toDouble();
    
    // Channel arrays
    for (int ch = 0; ch < 4; ++ch) {
        QString chStr = QString::number(ch);
        
        if (map.contains("dc" + chStr))
            params.dc[ch] = map["dc" + chStr].toDouble();
        if (map.contains("amplitude" + chStr))
            params.amplitude[ch] = map["amplitude" + chStr].toDouble();
        if (map.contains("frequency" + chStr))
            params.frequency[ch] = map["frequency" + chStr].toDouble();
        if (map.contains("phase" + chStr))
            params.phase[ch] = map["phase" + chStr].toDouble();
        if (map.contains("noise" + chStr))
            params.noiseLevel[ch] = map["noise" + chStr].toDouble();
    }
    
    return params;
}

void SineWaveTest::updateBufferUsage()
{
    emit bufferUsageChanged(bufferUsage());
}

#include "SineWaveTest.moc"
