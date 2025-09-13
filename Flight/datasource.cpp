#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include <QDebug>
#include <QTimer>
#include <QThread>

QT_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQueue<QPointF> *samplesQueue, QObject *parent) : QObject(parent)
{
    _working = false;
    _abort = false;
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    m_SamplesQueue = samplesQueue;
    m_index = 0;
    
    // Create timer for sine wave generation
    m_timer = new QTimer(this);
    m_timer->setInterval(1); // 1ms for 1kHz sampling rate
    connect(m_timer, &QTimer::timeout, this, &DataSource::generateSineWave);
}

DataSource::~DataSource()
{
    if (m_timer) {
        m_timer->stop();
    }
}

void DataSource::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug() << "Request DataSource worker start in Thread" << QThread::currentThreadId();
    mutex.unlock();

    // Start directly without thread for now
    doWork();
}

void DataSource::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug() << "Request DataSource worker aborting in Thread" << QThread::currentThreadId();
    }
    mutex.unlock();
}

void DataSource::doWork()
{
    qDebug() << "Starting DataSource sine wave generation in Thread" << QThread::currentThreadId();

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

    qDebug() << "DataSource sine wave generation started";
}

void DataSource::generateSineWave()
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
    
    // Debug print X and Y values
    qDebug() << "X:" << x << "Y:" << y;
    
    // Add point to queue using enqueue as requested
    m_SamplesQueue->enqueue(QPointF(x, y));
    
    // Increment index
    m_index++;
    
    // // Reset index if it gets too large to prevent overflow
    // if (m_index >= 1000000) {
    //     m_index = 0;
    // }
    
    // Emit update signal every REFRESH_POINTS
    if ((m_index % REFRESH_POINTS) == 0) {
        emit updateCurve();
    }
}

void DataSource::update(QAbstractSeries *series)
{
    if(series)
    {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(*m_SamplesQueue);
    }
}
