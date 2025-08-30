#ifndef OSCILLOSCOPEDATA_H
#define OSCILLOSCOPEDATA_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QVariantList>
#include <vector>
#include <deque>
#include <array>

// Data point structure for oscilloscope
struct DataPoint {
    double time;
    double value;
    
    DataPoint() : time(0.0), value(0.0) {}
    DataPoint(double t, double v) : time(t), value(v) {}
};

// Removed DataInputInterface - not needed for current implementation

// Main oscilloscope data manager
class OscilloscopeData : public QObject
{
    Q_OBJECT

public:
    explicit OscilloscopeData(QObject *parent = nullptr);
    ~OscilloscopeData();

    // QML interface methods
    Q_INVOKABLE void setRunning(bool running);
    Q_INVOKABLE void clearBuffer();
    Q_INVOKABLE void setTimeScale(int timeScaleIndex);
    Q_INVOKABLE QVariantList getChannelData(int channel);
    Q_INVOKABLE QVariantList getTimeData();
    
    // External data input method
    Q_INVOKABLE void addDataPoint(int channel, double time, double value);
    
    // Properties
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY runningChanged)
    Q_PROPERTY(int bufferSize READ bufferSize NOTIFY bufferSizeChanged)

    bool isRunning() const { return m_running; }
    int bufferSize() const { return m_bufferSize; }

signals:
    void runningChanged();
    void bufferSizeChanged();
    void dataUpdated();

private:
    void updateBufferSize();
    void startUpdateTimer();
    void stopUpdateTimer();
    
    // Data storage - ring buffers for each channel
    std::vector<std::deque<DataPoint>> m_channelBuffers;  // 4 channels
    
    // Update timer for chart refresh
    QTimer* m_updateTimer;
    
    // Configuration
    bool m_running;
    int m_timeScaleIndex;  // 0=0.1s/div, 1=0.5s/div, 2=1s/div
    int m_bufferSize;      // Dynamic: 1000, 5000, or 10000 points
    
    // Thread safety
    QMutex m_dataMutex;
    
    // Constants
    static constexpr int CHANNELS = 4;
    static constexpr int SAMPLE_RATE_HZ = 1000;  // 1 kHz
    static constexpr std::array<double, 3> TIME_SCALES = {0.1, 0.5, 1.0};
    static constexpr std::array<int, 3> BUFFER_SIZES = {1000, 5000, 10000};
};

#endif // OSCILLOSCOPEDATA_H