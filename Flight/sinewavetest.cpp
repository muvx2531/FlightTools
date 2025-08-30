#include "sinewavetest.h"
#include "oscilloscopedata.h"
#include <QDebug>

SineWaveTest::SineWaveTest(OscilloscopeData *oscilloscopeData, QObject *parent)
    : QObject(parent)
    , m_oscilloscopeData(oscilloscopeData)
    , m_sampleTimer(new QTimer(this))
    , m_startTime(0.0)
    , m_running(true)       // Always running
    , m_frequency(50.0)     // 50 Hz sine wave
    , m_amplitude(6.0)      // Amplitude = 6
    , m_phase(0.0)
{
    // Setup timer for 100Hz sampling (reduced from 1kHz for performance)
    m_sampleTimer->setTimerType(Qt::CoarseTimer);
    m_sampleTimer->setInterval(10);  // 10ms intervals = 100 Hz
    
    // Connect timer to sample generation
    connect(m_sampleTimer, &QTimer::timeout, this, &SineWaveTest::generateSample);
    
    qDebug() << "SineWaveTest: Initialized -" 
             << "Frequency:" << m_frequency << "Hz"
             << "Amplitude:" << m_amplitude
             << "Sample Rate:" << SAMPLE_RATE_HZ << "Hz";
             
    // Start immediately when application runs
    qDebug() << "SineWaveTest: Starting automatically...";
    m_elapsedTimer.start();
    m_sampleTimer->start();
    qDebug() << "SineWaveTest: Timer started, active:" << m_sampleTimer->isActive();
}

SineWaveTest::~SineWaveTest()
{
    stop();
}

void SineWaveTest::start()
{
    qDebug() << "SineWaveTest::start() called - Running:" << m_running << "OscilloscopeData:" << (m_oscilloscopeData ? "OK" : "NULL");
    
    if (!m_running && m_oscilloscopeData) {
        m_running = true;
        
        // Reset timing
        m_elapsedTimer.start();
        m_startTime = 0.0;
        m_phase = 0.0;
        
        // Start the precise timer
        m_sampleTimer->start();
        
        qDebug() << "SineWaveTest: *** STARTED *** generating" << m_frequency << "Hz sine wave with amplitude" << m_amplitude;
        qDebug() << "Timer interval:" << m_sampleTimer->interval() << "ms, Timer active:" << m_sampleTimer->isActive();
    } else {
        qDebug() << "SineWaveTest: Cannot start - Already running:" << m_running << "or no oscilloscope data";
    }
}

void SineWaveTest::stop()
{
    if (m_running) {
        m_running = false;
        m_sampleTimer->stop();
        
        qDebug() << "SineWaveTest: Stopped sine wave generation";
    }
}

void SineWaveTest::setFrequency(double frequency)
{
    if (frequency > 0.0 && frequency != m_frequency) {
        m_frequency = frequency;
        qDebug() << "SineWaveTest: Frequency changed to" << frequency << "Hz";
    }
}

void SineWaveTest::setAmplitude(double amplitude)
{
    if (amplitude >= 0.0 && amplitude != m_amplitude) {
        m_amplitude = amplitude;
        qDebug() << "SineWaveTest: Amplitude changed to" << amplitude;
    }
}

void SineWaveTest::generateSample()
{
    if (!m_running) {
        return;
    }
    
    // Calculate current time since start (in seconds)
    double currentTime = m_elapsedTimer.elapsed() / 1000.0;
    
    // Generate 50Hz sine wave: y = amplitude * sin(2π * frequency * time)
    double sineValue = m_amplitude * qSin(2.0 * M_PI * m_frequency * currentTime);
    
    // *** STEP 2: WRITE TO OSCILLOSCOPE BUFFER ***
    if (m_oscilloscopeData) {
        m_oscilloscopeData->addDataPoint(0, currentTime, sineValue);  // CH1 - 50Hz sine wave
    }
    
    // Minimal debug output - only every 100 samples (every 1 second at 100Hz)
    static int sampleCount = 0;
    sampleCount++;
    if (sampleCount % 100 == 0) {
        qDebug() << "SineWave: Generated" << sampleCount << "samples, value:" << QString::number(sineValue, 'f', 2);
    }
    
    // // Additional debug for first few samples
    // if (sampleCount <= 5) {
    //     qDebug() << "SineWave: First sample #" << sampleCount
    //              << "Time:" << currentTime << "Value:" << sineValue;
    // }
}
