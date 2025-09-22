#include "sinewaveworker.h"
#include <QThread>
#include <QDebug>
#include <QtMath>

SineWaveWorker::SineWaveWorker(QQueue<QPointF> *samplesQueue, QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;
    m_SamplesQueue = samplesQueue;
    m_refreshPoints = 5;  // Emit update every 5 points
    m_index = -1;
}

SineWaveWorker::~SineWaveWorker()
{
}

void SineWaveWorker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug() << "Request SineWaveWorker start in Thread" << QThread::currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void SineWaveWorker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug() << "Request SineWaveWorker aborting in Thread" << QThread::currentThreadId();
    }
    mutex.unlock();
}

void SineWaveWorker::doWork()
{
    qDebug() << "Starting SineWaveWorker process in Thread" << QThread::currentThreadId();

    bool abort = false;
    qreal x = 0;
    qreal y = 0;

    while(!abort)
    {
        mutex.lock();
        abort = _abort;
        mutex.unlock();

        // Remove old points if queue gets too large
        if(++m_index >= MAX_POINTS)
            m_SamplesQueue->dequeue();

        // Generate sine wave data
        // Time in seconds (10ms per point for smooth wave)
        qreal time = qreal(m_index) * 0.01;

        // Generate 5Hz sine wave: y = amplitude * sin(2π * frequency * time)
        y = AMPLITUDE * qSin(2.0 * M_PI * FREQUENCY * time);
        x = time;

        // Add point to queue
        m_SamplesQueue->enqueue(QPointF(x, y));

        // Debug output every 100 points
        if((m_index % 100) == 0)
        {
            qDebug() << "X:" << QString::number(x, 'f', 3) << "Y:" << QString::number(y, 'f', 3);
        }

        // Emit update signal
        if((m_index % m_refreshPoints) == 0)
        {
            emit updateCurve();
        }

        // Sleep for 10ms to create 100Hz sampling rate
        QThread::msleep(10);
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug() << "SineWaveWorker process finished in Thread" << QThread::currentThreadId();

    emit finished();
}
