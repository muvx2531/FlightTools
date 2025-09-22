import QtQuick 2.15
import QtQuick.Controls 2.15  
import QtQuick.Layouts 1.15
import QtCharts 2.15
import Flight.Backend 1.0

Rectangle {
    id: oscilloscopeRoot
    width: 900
    height: 480
    color: "#1a1a1a"
    border.color: "#333333"
    border.width: 2
    radius: 8

<<<<<<< HEAD
    // Simple properties
    property real range: 0.005
    property real refreshPoints: 0.005
    property bool isRunning: false
=======
    // Backend data source
    SineWaveTest {
        id: sineWaveBackend
        
        onRunningChanged: function(running) {
            oscilloscopeRoot.isRunning = running
        }
        
        onSampleRateChanged: function(rate) {
            oscilloscopeRoot.currentSampleRate = rate
        }
        
        onBufferUsageChanged: function(usage) {
            oscilloscopeRoot.bufferUsage = usage
        }
    }
    
    // UI properties
    property bool isRunning: true  // Start with display running
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
    property var channelEnabled: [true, true, true, true]
    property var channelColors: ["#00ff00", "#ffff00", "#ff6600", "#ff0088"]
    property var channelLabels: ["CH1", "CH2", "CH3", "CH4"]
    
<<<<<<< HEAD
    // Frame rate properties - handled by backend
    property real currentFPS: 0
=======
    // Performance monitoring
    property real currentSampleRate: 1000.0
    property int bufferUsage: 0
    property int updateCount: 0
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
    
    // Fixed time scale: 0.1s/div
    property real fixedTimeScale: 0.1
    property string fixedTimeScaleLabel: "0.1s/div"
    
    // Amplitude scale options: comprehensive range from small to large scales
    property var amplitudeScales: [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0]
    property var amplitudeScaleLabels: ["0.01/div", "0.02/div", "0.05/div", "0.1/div", "0.2/div", "0.5/div", "1/div", "2/div", "5/div", "10/div", "20/div", "50/div", "100/div"]
    property int currentAmplitudeScaleIndex: 6  // Default to 1/div

    Component.onCompleted: {
<<<<<<< HEAD
        console.log("Simple oscilloscope loaded")
=======
        console.log("Oscilloscope with SineWaveTest backend loaded")
        // Start the backend automatically
        sineWaveBackend.start()
    }
    
    Component.onDestruction: {
        sineWaveBackend.stop()
    }
    
    // Backend data processing
    function addSamples(timestamps, ch0, ch1, ch2, ch3) {
        var channels = [channel1, channel2, channel3, channel4]
        var channelData = [ch0, ch1, ch2, ch3]
        
        if (timestamps.length === 0) return
        
        var currentTimeScale = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex]
        var currentAmplitudeScale = oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex]
        var timeWindow = currentTimeScale * 10
        
        // Add new points to each enabled channel
        for (var ch = 0; ch < 4; ch++) {
            if (!oscilloscopeRoot.channelEnabled[ch]) continue
            
            var series = channels[ch]
            var data = channelData[ch]
            
            // Add all new points
            for (var i = 0; i < timestamps.length; i++) {
                var scaledValue = data[i] * currentAmplitudeScale
                series.append(timestamps[i], scaledValue)
            }
            
            // Remove old points to maintain performance
            var maxPoints = 1000
            if (series.count > maxPoints) {
                series.removePoints(0, series.count - maxPoints)
            }
        }
        
        // Auto-scale time axis
        var lastTime = timestamps[timestamps.length - 1]
        if (lastTime > timeWindow) {
            timeAxis.min = lastTime - timeWindow
            timeAxis.max = lastTime
        } else {
            timeAxis.min = 0
            timeAxis.max = timeWindow
        }
        
        // Update counter for performance monitoring
        oscilloscopeRoot.updateCount++
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        // Left Control Panel
        Rectangle {
            Layout.preferredWidth: 180
            Layout.fillHeight: true
            color: "#2a2a2a"
            border.color: "#404040"
            border.width: 1
            radius: 6

            Column {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 8

                Text {
                    text: "OSCILLOSCOPE"
                    color: "#00aaff"
                    font.pointSize: 10
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                // FPS Display
                Rectangle {
                    width: parent.width
                    height: 20
                    color: "#1a1a1a"
                    border.color: "#404040"
                    border.width: 1
                    radius: 3
                    
                    Text {
                        anchors.centerIn: parent
                        text: "Rate: " + oscilloscopeRoot.currentSampleRate.toFixed(0) + " Hz"
                        color: oscilloscopeRoot.currentSampleRate >= 900 ? "#00ff00" : 
                               oscilloscopeRoot.currentSampleRate >= 500 ? "#ffff00" : "#ff0000"
                        font.pointSize: 8
                        font.bold: true
                    }
                }

                Button {
                    id: startStopButton
                    width: parent.width
                    height: 35
                    text: oscilloscopeRoot.isRunning ? "⏸ STOP" : "▶ START"
                    enabled: !buttonDebounceTimer.running
                    
                    background: Rectangle {
                        color: {
                            if (!parent.enabled) return "#666666"
                            return oscilloscopeRoot.isRunning ? "#ff4444" : "#00aa44"
                        }
                        radius: 4
                        border.color: {
                            if (!parent.enabled) return "#888888"
                            return oscilloscopeRoot.isRunning ? "#ff6666" : "#00cc55"
                        }
                        border.width: 1
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: parent.enabled ? "white" : "#aaaaaa"
                        font.pointSize: 9
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    
                    onClicked: {
                        // Start debounce timer to prevent rapid clicks
                        buttonDebounceTimer.start()
                        
                        // Toggle display timer (FPS), not the backend
                        if (oscilloscopeRoot.isRunning) {
                            console.log("Stopping display timer...")
                            oscilloscopeRoot.isRunning = false
                        } else {
                            console.log("Starting display timer...")
                            oscilloscopeRoot.isRunning = true
                        }
                    }
                    
                    // Debounce timer to prevent rapid button clicks
                    Timer {
                        id: buttonDebounceTimer
                        interval: 500  // 500ms debounce
                        repeat: false
                    }
                }

                Button {
                    id: clearButton
                    width: parent.width
                    height: 30
                    text: "🗑 CLEAR"
                    
                    background: Rectangle {
                        color: clearButton.pressed ? "#ff8800" : "#ffaa00"
                        radius: 4
                        border.color: clearButton.pressed ? "#ffaa00" : "#ffcc33"
                        border.width: 1
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: "black"
                        font.pointSize: 9
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    
                    onClicked: {
<<<<<<< HEAD
                        // Clear chart series and reset timer
                        oscilloscopeChart.series("CH1").clear()
                        oscilloscopeChart.series("CH2").clear()
                        oscilloscopeChart.series("CH3").clear()
                        oscilloscopeChart.series("CH4").clear()

                        timeAxis.max = 2000;  // 2 seconds
                        timeAxis.min = 0;
                        
                        // Timer reset not needed anymore
                        
                        // Reset FPS counter
                        oscilloscopeRoot.currentFPS = 0
                        
                        // Reset time axis to initial state
                        var timeWindow = oscilloscopeRoot.fixedTimeScale * 10  // 0.1 * 10 = 1.0 second
                        oscilloscopeChart.axisX().min = 0
                        oscilloscopeChart.axisX().max = timeWindow
=======
                        // Clear chart series
                        channel1.clear()
                        channel2.clear()
                        channel3.clear()
                        channel4.clear()
                        
                        // Reset counters
                        oscilloscopeRoot.updateCount = 0
                        
                        // Reset time axis to initial state
                        var currentTimeScale = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex]
                        var timeWindow = currentTimeScale * 10
                        timeAxis.min = 0
                        timeAxis.max = timeWindow
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
                        
                        console.log("Oscilloscope cleared")
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#404040"
                }

                // Channel Enable/Disable Controls
                Text {
                    text: "CHANNELS"
                    color: "#00aaff"
                    font.pointSize: 9
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Column {
                    width: parent.width
                    spacing: 4

                    Repeater {
                        model: 4
                        delegate: Row {
                            width: parent.width
                            spacing: 8

                            Rectangle {
                                width: 12
                                height: 12
                                anchors.verticalCenter: parent.verticalCenter
                                color: oscilloscopeRoot.channelColors[index]
                                border.color: "#666666"
                                border.width: 1
                                radius: 2
                            }

                            CheckBox {
                                id: channelCheckBox
                                anchors.verticalCenter: parent.verticalCenter
                                
                                Component.onCompleted: {
                                    checked = oscilloscopeRoot.channelEnabled[index]
                                }
                                
                                onCheckedChanged: {
                                    if (oscilloscopeRoot.channelEnabled[index] !== checked) {
                                        var newChannelEnabled = oscilloscopeRoot.channelEnabled.slice()
                                        newChannelEnabled[index] = checked
                                        oscilloscopeRoot.channelEnabled = newChannelEnabled
                                    }
                                }

                                indicator: Rectangle {
                                    implicitWidth: 16
                                    implicitHeight: 16
                                    x: channelCheckBox.leftPadding
                                    y: parent.height / 2 - height / 2
                                    radius: 2
                                    border.color: channelCheckBox.down ? "#17a81a" : "#21be2b"
                                    border.width: channelCheckBox.visualFocus ? 2 : 1
                                    color: channelCheckBox.down ? "#17a81a" : (channelCheckBox.checked ? "#21be2b" : "#404040")

                                    Rectangle {
                                        width: 6
                                        height: 6
                                        x: 5
                                        y: 5
                                        radius: 1
                                        color: parent.parent.down ? "#f6f6f6" : "#ffffff"
                                        visible: channelCheckBox.checked
                                    }
                                }
                            }

                            Text {
                                text: oscilloscopeRoot.channelLabels[index]
                                color: oscilloscopeRoot.channelEnabled[index] ? "#ffffff" : "#666666"
                                font.pointSize: 8
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#404040"
                }

                // Fixed Time Scale Display
                Text {
                    text: "TIME SCALE"
                    color: "#00aaff"
                    font.pointSize: 9
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Rectangle {
                    width: parent.width
                    height: 30
                    color: "#2a2a2a"
                    border.color: "#00aaff"
                    border.width: 1
                    radius: 4

                    Text {
                        text: oscilloscopeRoot.fixedTimeScaleLabel
                        color: "#ffffff"
                        font.pointSize: 9
                        font.bold: true
                        anchors.centerIn: parent
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#404040"
                }

                // Amplitude Scale Controls
                Text {
                    text: "AMPLITUDE"
                    color: "#00aaff"
                    font.pointSize: 9
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ComboBox {
                    id: amplitudeScaleCombo
                    width: parent.width
                    height: 30
                    model: oscilloscopeRoot.amplitudeScaleLabels
                    currentIndex: oscilloscopeRoot.currentAmplitudeScaleIndex
                    
                    onCurrentIndexChanged: {
                        oscilloscopeRoot.currentAmplitudeScaleIndex = currentIndex
                        console.log("Amplitude scale changed to:", oscilloscopeRoot.amplitudeScaleLabels[currentIndex])
                    }
                    
                    background: Rectangle {
                        color: amplitudeScaleCombo.down ? "#404040" : "#2a2a2a"
                        border.color: amplitudeScaleCombo.activeFocus ? "#00aaff" : "#555555"
                        border.width: 1
                        radius: 4
                    }
                    
                    contentItem: Text {
                        text: amplitudeScaleCombo.displayText
                        color: "#ffffff"
                        font.pointSize: 8
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 8
                        rightPadding: 8
                    }
                    
                    indicator: Text {
                        x: amplitudeScaleCombo.width - width - 8
                        y: amplitudeScaleCombo.height / 2 - height / 2
                        text: "▼"
                        color: "#00aaff"
                        font.pointSize: 8
                    }
                    
                    popup: Popup {
                        y: amplitudeScaleCombo.height
                        width: amplitudeScaleCombo.width
                        height: Math.min(200, amplitudeScaleCombo.model.length * 25 + 2)
                        padding: 1
                        
                        contentItem: ListView {
                            anchors.fill: parent
                            model: amplitudeScaleCombo.delegateModel
                            currentIndex: amplitudeScaleCombo.highlightedIndex
                            clip: true
                        }
                        
                        background: Rectangle {
                            color: "#2a2a2a"
                            border.color: "#555555"
                            border.width: 1
                            radius: 4
                        }
                    }
                    
                    delegate: ItemDelegate {
                        width: amplitudeScaleCombo.width
                        height: 25
                        
                        background: Rectangle {
                            color: parent.hovered ? "#404040" : "#2a2a2a"
                            radius: 2
                        }
                        
                        contentItem: Text {
                            text: modelData
                            color: "#ffffff"
                            font.pointSize: 8
                            verticalAlignment: Text.AlignVCenter
                            leftPadding: 8
                        }
                    }
                }
            }
        }

        // Simple Oscilloscope ChartView
        ChartView {
            id: oscilloscopeChart
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            theme: ChartView.ChartThemeDark
            backgroundColor: "#000000"
            plotAreaColor: "#000a0a"
            antialiasing: true
            animationOptions: ChartView.NoAnimation
            legend.visible: false
            
            // Time axis (X)
            ValueAxis {
                id: timeAxis
                min: 0
                max: 2000  // 2 seconds of data (2000ms)
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"
                titleText: "Time (" + oscilloscopeRoot.fixedTimeScaleLabel + ")"
                titleBrush: Qt.rgba(0, 1, 0, 1)
            }
            
            // Amplitude axis (Y)
            ValueAxis {
                id: amplitudeAxis
                min: -oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 5
                max: oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 5
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"
                titleText: "Amplitude (" + oscilloscopeRoot.amplitudeScaleLabels[oscilloscopeRoot.currentAmplitudeScaleIndex] + ")"
                titleBrush: Qt.rgba(0, 1, 0, 1)
            }
            
            // Channel 1
            LineSeries {
                id: channel1
                name: "CH1"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[0]
                width: 2
                visible: oscilloscopeRoot.channelEnabled[0]
                useOpenGL: openGLSupported
            }
            
            // Channel 2
            LineSeries {
                id: channel2
                name: "CH2"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[1]
                width: 2
                visible: oscilloscopeRoot.channelEnabled[1]
                useOpenGL: openGLSupported
            }
            
            // Channel 3
            LineSeries {
                id: channel3
                name: "CH3"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[2]
                width: 2
                visible: oscilloscopeRoot.channelEnabled[2]
                useOpenGL: openGLSupported
            }
            
            // Channel 4
            LineSeries {
                id: channel4
                name: "CH4"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[3]
                width: 2
                visible: oscilloscopeRoot.channelEnabled[3]
                useOpenGL: openGLSupported
            }
            
<<<<<<< HEAD
            // Timer removed - data updates handled by backend
        }
    }

    // Connections to DataSource for real-time data updates
    Connections {
        target: dataSource

        function onUpdateCurve() {
            //console.log("Updating oscilloscope with new data")
            console.log("Channel1 count: " + channel1.count + " timeAxis max: " + timeAxis.max + " min: " + timeAxis.min)

            // Update time axis (scrolling window)
            // With 1000Hz sampling (1ms intervals), we get 1000 points per second
            if(channel1.count >= 2000) { // Start scrolling after 2 seconds of data
                timeAxis.max += 10;  // Scroll by 20ms
                timeAxis.min = timeAxis.max - 2000;  // Keep 2 second window
            }

            // Update the chart series with new data from DataSource
            if (dataSource && oscilloscopeChart.series("CH1")) {
                dataSource.update(oscilloscopeChart.series("CH1"));
                // Debug: console.log("CH1 series updated")
            }
=======
        }
    }
    
    // Backend data flush timer (30 Hz)
    Timer {
        id: flushTimer
        interval: 33  // ~30 Hz
        running: oscilloscopeRoot.isRunning
        repeat: true
        
        onTriggered: {
            // Flush data from backend to QML
            sineWaveBackend.flushToQml(oscilloscopeRoot)
>>>>>>> bc523e3f8eae207881223cc6b330ef17e9f38592
        }
    }
}
