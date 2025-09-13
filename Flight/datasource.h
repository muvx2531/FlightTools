#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QQueue>
#include <QFile>
#include <QMutex>
#include <QTimer>
#include <QPointF>

QT_BEGIN_NAMESPACE
class QAbstractSeries;
QT_END_NAMESPACE

QT_USE_NAMESPACE

#define X_POINTS 703

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQueue<QPointF> *samplesQueue, QObject *parent = nullptr);
    ~DataSource();
    void requestWork();
    void abort();

signals:
    void updateCurve();
    void workRequested();
    void finished();

public slots:
    void update(QAbstractSeries *series);
    void doWork();

private slots:
    void generateSineWave();

private:
    // Threading control (like SamplerWorker)
    bool _abort;
    bool _working;
    QMutex mutex;
    
    QQueue<QPointF> *m_SamplesQueue;
    QTimer *m_timer;
    int m_index;
    
    // Sine wave parameters
    static const int SAMPLING_RATE = 1000;  // 1 kHz
    static const int FREQUENCY = 5;         // 5 Hz
    static const int MAX_POINTS = 5000;     // Limit to 5000 points
    static const int AMPLITUDE = 5;      // Amplitude of sine wave
    static const int REFRESH_POINTS = 10;   // Emit update every 10 points
};

#endif // DATASOURCE_H
