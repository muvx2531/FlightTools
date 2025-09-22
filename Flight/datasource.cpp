#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QDebug>
#include <QThread>
#include <QtMath>
#include <QEventLoop>

QT_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
    Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQueue<QPointF> *samplesQueue, QObject *parent) : QObject(parent)
{
    //m_index = -1;
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    m_SamplesQueue = samplesQueue;
}

DataSource::~DataSource()
{

    qDebug() << "DataSource destroyed";
}


void DataSource::update(QAbstractSeries *series)
{
    if(series)
    {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(*m_SamplesQueue);
    }
}

