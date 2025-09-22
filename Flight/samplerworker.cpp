#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <QDate>
#include <QtCharts/QXYSeries>
#include <QtMath>
#include <QtCore/QRandomGenerator>
#include "samplerworker.h"



SamplerWorker::SamplerWorker(QQueue<QPointF> *samplesQueue, QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;
    m_SamplesQueue = samplesQueue;
    m_adcFile.setFileName("/sys/bus/iio/devices/iio:device0/in_voltage1_raw");
    m_dataSource = DATASOURCE_ADC;
    m_refreshPoints = 10;
    m_index = -1;
}

SamplerWorker::~SamplerWorker()
{

}

void SamplerWorker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void SamplerWorker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void SamplerWorker::setSource(int source)
{
    m_dataSource = source;
    if(source == DATASOURCE_ADC)
        m_refreshPoints = 100;
    else
        m_refreshPoints = 10;
    m_index = -1;
    m_SamplesQueue->clear();
}

void SamplerWorker::doWork()
{
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

    bool abort = false;
    qreal x = 0;
    qreal y = 0;
    int yValue = 0;


    quint8 inByte;
    int numByte = 0;
    int receiverStatus = RCV_ST_IDLE;
    Frame *m_inFrame = nullptr;
    quint8 checksum = 0, xored = 0x00;
    int dataLength = 0;

    // Serial Port Initialization
    m_Serial = new QSerialPort();
    m_Serial->setPortName("ttyUSB0");
    m_Serial->setBaudRate(QSerialPort::Baud115200);
    m_Serial->setDataBits(QSerialPort::Data8);
    m_Serial->setParity(QSerialPort::NoParity);
    m_Serial->setStopBits(QSerialPort::OneStop);
    m_Serial->setFlowControl(QSerialPort::NoFlowControl);
    m_Serial->open(QIODevice::ReadWrite);
    qDebug() << "SerialPort Status: " << m_Serial->isOpen();


    while(!abort)
    {
        mutex.lock();
        abort = _abort;
        mutex.unlock();

        QThread::usleep(100);
                                       // READ DATA FROM SERIAL

        if(++m_index >= 2100)
            m_SamplesQueue->dequeue();

        // Generate 5Hz sine wave for testing
        // Sampling rate: 10kHz, frequency: 5Hz
        // Time = m_index / 10000.0 seconds
        qreal time = m_index / 10000.0;
        y = 5.0 * qSin(2.0 * M_PI * 50.0 * time); // 5Hz sine wave with amplitude 100
        x = qreal(m_index);
        m_SamplesQueue->enqueue(QPointF(x, y));
        qDebug() << "sine wave "<<x<<" "<<y<<" m_index "<<m_index;
        if((m_index % m_refreshPoints) == 0)
        {
            emit updateCurve();
            qDebug() << "update Curve";
        }
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    emit finished();
}


