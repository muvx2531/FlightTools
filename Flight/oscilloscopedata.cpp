#include "oscilloscopedata.h"
#include <QDebug>
#include <QtMath>
#include <QCoreApplication>

// =============================================================================
// OscilloscopeData Implementation  
// =============================================================================

OscilloscopeData::OscilloscopeData(QObject *parent)
    : QObject(parent)
    , m_running(false)
    , m_timeScaleIndex(2)  // Default to 1s/div (10000 points)
    , m_bufferSize(10000)
    , m_updateTimer(new QTimer(this))
{
    // Initialize channel buffers
    m_channelBuffers.resize(CHANNELS);
    
    // Setup update timer for 15 FPS chart refresh (reduced for performance)
    m_updateTimer->setInterval(67);  // 67ms = ~15 FPS
    connect(m_updateTimer, &QTimer::timeout, this, &OscilloscopeData::dataUpdated);
    
    updateBufferSize();
    
    qDebug() << "OscilloscopeData: Initialized with" << CHANNELS << "channels, buffer size:" << m_bufferSize;
}

OscilloscopeData::~OscilloscopeData()
{
    // Clean shutdown
    setRunning(false);
}

void OscilloscopeData::setRunning(bool running)
{
    if (m_running != running) {
        m_running = running;
        
        if (running) {
            // Clear buffers when starting
            clearBuffer();
            startUpdateTimer();
            qDebug() << "OscilloscopeData: Ready to receive data, update timer started";
        } else {
            stopUpdateTimer();
            qDebug() << "OscilloscopeData: Stopped data acquisition, update timer stopped";
        }
        
        emit runningChanged();
    }
}

void OscilloscopeData::clearBuffer()
{
    QMutexLocker locker(&m_dataMutex);
    
    for (auto& buffer : m_channelBuffers) {
        buffer.clear();
    }
    
    qDebug() << "OscilloscopeData: Cleared all channel buffers";
    emit dataUpdated();
}

void OscilloscopeData::setTimeScale(int timeScaleIndex)
{
    if (timeScaleIndex >= 0 && timeScaleIndex < 3 && m_timeScaleIndex != timeScaleIndex) {
        m_timeScaleIndex = timeScaleIndex;
        
        // Update buffer size and clear old data
        updateBufferSize();
        clearBuffer();
        
        qDebug() << "OscilloscopeData: Time scale changed to index" << timeScaleIndex 
                 << "(" << TIME_SCALES[timeScaleIndex] << "s/div), buffer size:" << m_bufferSize;
    }
}

QVariantList OscilloscopeData::getChannelData(int channel)
{
    QVariantList result;
    
    if (channel < 0 || channel >= CHANNELS) {
        return result;
    }
    
    QMutexLocker locker(&m_dataMutex);
    
    const auto& buffer = m_channelBuffers[channel];
    result.reserve(buffer.size() * 2); // time and value pairs
    
    for (const auto& point : buffer) {
        QVariantMap dataPoint;
        dataPoint["time"] = point.time;
        dataPoint["value"] = point.value;
        result.append(dataPoint);
    }
    
    return result;
}

QVariantList OscilloscopeData::getTimeData()
{
    QVariantList result;
    
    QMutexLocker locker(&m_dataMutex);
    
    // Get time data from channel 0 (all channels should have same timestamps)
    if (!m_channelBuffers.empty() && !m_channelBuffers[0].empty()) {
        const auto& buffer = m_channelBuffers[0];
        result.reserve(buffer.size());
        
        for (const auto& point : buffer) {
            result.append(point.time);
        }
    }
    
    return result;
}

void OscilloscopeData::addDataPoint(int channel, double time, double value)
{
    if (channel < 0 || channel >= CHANNELS || !m_running) {
        return;
    }
    
    QMutexLocker locker(&m_dataMutex);
    
    auto& buffer = m_channelBuffers[channel];
    
    // Add new data point
    buffer.emplace_back(time, value);
    
    // Maintain ring buffer size - remove old data if exceeding capacity
    while (static_cast<int>(buffer.size()) > m_bufferSize) {
        buffer.pop_front();
    }
    
    // Data is added - update signal will be emitted by timer at 30 FPS
    // This prevents overwhelming the QML with too many updates
}

void OscilloscopeData::updateBufferSize()
{
    int newSize = BUFFER_SIZES[m_timeScaleIndex];
    
    if (m_bufferSize != newSize) {
        m_bufferSize = newSize;
        
        // Resize all channel buffers (this will clear existing data)
        QMutexLocker locker(&m_dataMutex);
        for (auto& buffer : m_channelBuffers) {
            if (static_cast<int>(buffer.size()) > m_bufferSize) {
                // Keep only the most recent data
                while (static_cast<int>(buffer.size()) > m_bufferSize) {
                    buffer.pop_front();
                }
            }
        }
        
        emit bufferSizeChanged();
    }
}

void OscilloscopeData::startUpdateTimer()
{
    if (!m_updateTimer->isActive()) {
        m_updateTimer->start();
        qDebug() << "OscilloscopeData: Update timer started (30 FPS)";
    }
}

void OscilloscopeData::stopUpdateTimer()
{
    if (m_updateTimer->isActive()) {
        m_updateTimer->stop();
        qDebug() << "OscilloscopeData: Update timer stopped";
    }
}