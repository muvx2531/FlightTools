import QtQuick 2.15
import QtQuick.Controls 2.15  
import QtQuick.Layouts 1.15
import QtCharts 2.15

Rectangle {
    id: oscilloscopeRoot
    width: 900
    height: 480
    color: "#1a1a1a"
    border.color: "#333333"
    border.width: 2
    radius: 8

    // Simple properties
    property bool isRunning: false
    property var channelEnabled: [true, true, true, true]
    property var channelColors: ["#00ff00", "#ffff00", "#ff6600", "#ff0088"]
    property var channelLabels: ["CH1", "CH2", "CH3", "CH4"]

    Component.onCompleted: {
        console.log("Simple oscilloscope loaded")
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

                Button {
                    id: startStopButton
                    width: parent.width
                    height: 35
                    text: oscilloscopeRoot.isRunning ? "⏸ STOP" : "▶ START"
                    
                    background: Rectangle {
                        color: oscilloscopeRoot.isRunning ? "#ff4444" : "#00aa44"
                        radius: 4
                        border.color: oscilloscopeRoot.isRunning ? "#ff6666" : "#00cc55"
                        border.width: 1
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        font.pointSize: 9
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    
                    onClicked: {
                        oscilloscopeRoot.isRunning = !oscilloscopeRoot.isRunning
                        console.log("Oscilloscope running:", oscilloscopeRoot.isRunning)
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
                        // Clear chart series and reset timer
                        oscilloscopeChart.channel1.clear()
                        oscilloscopeChart.channel2.clear()
                        oscilloscopeChart.channel3.clear()
                        oscilloscopeChart.channel4.clear()
                        demoTimer.time = 0
                        console.log("Oscilloscope cleared")
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
                max: 10
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"
                titleText: "Time (s)"
                titleBrush: Qt.rgba(0, 1, 0, 1)
            }
            
            // Amplitude axis (Y)
            ValueAxis {
                id: amplitudeAxis
                min: -25
                max: 25
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"
                titleText: "Amplitude"
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
            
            // Simple demo timer to show the oscilloscope is working
            Timer {
                id: demoTimer
                interval: 100  // 100ms = 10 updates per second
                running: oscilloscopeRoot.isRunning
                repeat: true
                property real time: 0
                
                onTriggered: {
                    time += 0.1
                    var channels = [channel1, channel2, channel3, channel4]
                    
                    // Generate simple sine waves for each channel
                    for (var ch = 0; ch < 4; ch++) {
                        if (!oscilloscopeRoot.channelEnabled[ch]) continue
                        
                        var frequency = (ch + 1) * 0.5  // Different frequencies
                        var amplitude = 5 * (ch + 1)     // Different amplitudes
                        var value = amplitude * Math.sin(2 * Math.PI * frequency * time)
                        
                        channels[ch].append(time, value)
                        
                        // Keep only last 100 points for performance
                        if (channels[ch].count > 100) {
                            channels[ch].removePoints(0, channels[ch].count - 100)
                        }
                    }
                    
                    // Auto-scale time axis to show scrolling window
                    if (time > 10) {
                        timeAxis.min = time - 10
                        timeAxis.max = time
                    }
                }
            }
        }
    }
}