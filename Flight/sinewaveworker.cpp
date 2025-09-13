#include "sinewaveworker.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QtMath>
#include <QPointF>

SineWaveWorker::SineWaveWorker(QQueue<QPointF> *samplesQueue, QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;
    m_SamplesQueue = samplesQueue;
    m_index = 0;
    m_timer = new QTimer(this);
    
    // Set timer interval for 1kHz sampling rate (1ms)
    m_timer->setInterval(1);
    connect(m_timer, &QTimer::timeout, this, &SineWaveWorker::generateSineWave);
}

SineWaveWorker::~SineWaveWorker()
{
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
}

void SineWaveWorker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug() << "Request sine wave worker start in Thread" << thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void SineWaveWorker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug() << "Request sine wave worker aborting in Thread" << thread()->currentThreadId();
    }
    mutex.unlock();
}

void SineWaveWorker::doWork()
{
    qDebug() << "Starting sine wave worker process in Thread" << thread()->currentThreadId();

    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    if (!abort) {
        // Reset index and clear queue
        m_index = 0;
        m_SamplesQueue->clear();
        
        // Start the timer to generate sine wave data
        m_timer->start();
    }

    // Keep the worker running until abort is requested
    while (!abort) {
        QThread::msleep(100); // Sleep for 100ms to avoid busy waiting
        
        mutex.lock();
        abort = _abort;
        mutex.unlock();
    }

    // Stop the timer when aborting
    m_timer->stop();

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug() << "Sine wave worker process finished in Thread" << thread()->currentThreadId();

    emit finished();
}

void SineWaveWorker::generateSineWave()
{
    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    if (abort) {
        m_timer->stop();
        return;
    }

    // Manage queue size - remove oldest points if exceeding MAX_POINTS
    if (m_SamplesQueue->size() >= MAX_POINTS) {
        m_SamplesQueue->dequeue();
    }

    // Calculate time in seconds
    qreal time = qreal(m_index) / SAMPLING_RATE;
    
    // Generate 5Hz sine wave: y = amplitude * sin(2π * frequency * time)
    qreal y = AMPLITUDE * qSin(2.0 * M_PI * FREQUENCY * time);
    
    // Use time as x-axis (in seconds)
    qreal x = time;
    
    // Add point to queue
    m_SamplesQueue->enqueue(QPointF(x, y));
    
    // Increment index
    m_index++;
    
    // Reset index if it gets too large to prevent overflow
    if (m_index >= 1000000) {
        m_index = 0;
    }
    
    // Emit update signal every REFRESH_POINTS
    if ((m_index % REFRESH_POINTS) == 0) {
        emit updateCurve();
    }
}
