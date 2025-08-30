#ifndef SINEWAVETEST_H
#define SINEWAVETEST_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QtMath>

class OscilloscopeData; // Forward declaration

/**
 * @brief Sine wave generator for testing oscilloscope
 * 
 * Generates a 50Hz sine wave with amplitude 6 and feeds it to the oscilloscope buffer
 * at 1kHz sampling rate (1 sample every 1ms)
 */
class SineWaveTest : public QObject
{
    Q_OBJECT

public:
    explicit SineWaveTest(OscilloscopeData *oscilloscopeData, QObject *parent = nullptr);
    ~SineWaveTest();

    // Control methods
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE bool isRunning() const { return m_running; }
    
    // Configuration
    Q_INVOKABLE void setFrequency(double frequency);
    Q_INVOKABLE void setAmplitude(double amplitude);
    Q_INVOKABLE double getFrequency() const { return m_frequency; }
    Q_INVOKABLE double getAmplitude() const { return m_amplitude; }

private slots:
    void generateSample();

private:
    // Oscilloscope data reference
    OscilloscopeData *m_oscilloscopeData;
    
    // Timing
    QTimer *m_sampleTimer;
    QElapsedTimer m_elapsedTimer;
    double m_startTime;
    
    // Wave generation parameters
    bool m_running;
    double m_frequency;     // 50 Hz
    double m_amplitude;     // 6.0
    double m_phase;         // Current phase
    
    // Sampling rate
    static constexpr int SAMPLE_RATE_HZ = 100;  // 100 Hz (reduced for performance)
    static constexpr int SAMPLE_INTERVAL_MS = 1000 / SAMPLE_RATE_HZ;  // 10 ms
};

#endif // SINEWAVETEST_H