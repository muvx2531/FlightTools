#ifndef SINEWAVETEST_H
#define SINEWAVETEST_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>
#include "RingBuffer.h"
#include <cmath>
#include <random>

struct SampleData {
    double t;     // Timestamp in seconds
    float y0, y1, y2, y3;  // Channel values
};

struct GeneratorParams {
    double sampleRate = 1000.0;  // Hz
    double dc[4] = {0.0, 0.0, 0.0, 0.0};
    double amplitude[4] = {1.0, 1.0, 1.0, 1.0};
    double frequency[4] = {1.0, 2.0, 3.0, 4.0};  // Hz
    double phase[4] = {0.0, 35.0, 70.0, 105.0};  // degrees
    double noiseLevel[4] = {0.01, 0.01, 0.01, 0.01};
};

class SineWaveWorker : public QObject
{
    Q_OBJECT

public:
    explicit SineWaveWorker(RingBuffer<SampleData, 65536>* buffer, QObject* parent = nullptr);
    
    void setParams(const GeneratorParams& params);
    GeneratorParams getParams() const;

public slots:
    void start();
    void stop();
    void reconfigure(const GeneratorParams& params);

private slots:
    void generateSamples();

private:
    RingBuffer<SampleData, 65536>* m_buffer;
    QTimer* m_timer;
    QElapsedTimer m_elapsedTimer;
    GeneratorParams m_params;
    mutable QMutex m_paramsMutex;
    
    uint64_t m_sampleCounter;
    bool m_running;
    
    // Random number generation
    std::mt19937 m_rng;
    std::normal_distribution<double> m_noiseDist;
    
    static constexpr int SAMPLES_PER_BATCH = 100;  // Generate samples in batches
};

class SineWaveTest : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(double sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
    Q_PROPERTY(int bufferUsage READ bufferUsage NOTIFY bufferUsageChanged)

public:
    explicit SineWaveTest(QObject* parent = nullptr);
    ~SineWaveTest();
    
    bool running() const { return m_running; }
    double sampleRate() const;
    int bufferUsage() const;
    
    Q_INVOKABLE void start();
    Q_INVOKABLE void start(const QVariantMap& params);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void reconfigure(const QVariantMap& params);
    
    // Called from UI thread at 30 Hz to flush data to QML
    Q_INVOKABLE void flushToQml(QObject* qmlOscilloscope);

public slots:
    void setSampleRate(double rate);

signals:
    void runningChanged(bool running);
    void sampleRateChanged(double rate);
    void bufferUsageChanged(int usage);
    void samplesReady(const QVariantList& timestamps, const QVariantList& channel0,
                     const QVariantList& channel1, const QVariantList& channel2, 
                     const QVariantList& channel3);

private:
    GeneratorParams variantMapToParams(const QVariantMap& map) const;
    void updateBufferUsage();
    
    RingBuffer<SampleData, 65536> m_buffer;
    SineWaveWorker* m_worker;
    QThread* m_workerThread;
    QTimer* m_flushTimer;
    
    bool m_running;
    mutable QMutex m_mutex;
    
    static constexpr int MAX_BATCH_SIZE = 5000;
    static constexpr double UI_UPDATE_RATE = 30.0;  // Hz
    static constexpr int DEFAULT_DISPLAY_RATE = 150;  // points/sec/channel
};

#endif // SINEWAVETEST_H