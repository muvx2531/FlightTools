#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QQueue>
#include <QFile>

QT_BEGIN_NAMESPACE
class QAbstractSeries;
QT_END_NAMESPACE

QT_USE_NAMESPACE



class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQueue<QPointF> *samplesQueue, QObject *parent = nullptr);
    ~DataSource();
signals:
    void updateCurve();

public slots:
    void update(QAbstractSeries *series);
    //void timerTrigger();
private:
    QQueue<QPointF> *m_SamplesQueue;
    //int m_index;
};

#endif // DATASOURCE_H
