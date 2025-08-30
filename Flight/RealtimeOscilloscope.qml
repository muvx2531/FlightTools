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
    
    // Frame rate properties
    property int targetFPS: 30
    property real currentFPS: 0
    property int frameCount: 0
    property real lastFPSTime: 0
    
    // Time scale options: more comprehensive range
    property var timeScales: [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0]
    property var timeScaleLabels: ["0.01s/div", "0.02s/div", "0.05s/div", "0.1s/div", "0.2s/div", "0.5s/div", "1s/div", "2s/div", "5s/div", "10s/div"]
    property int currentTimeScaleIndex: 6  // Default to 1s/div
    
    // Amplitude scale options: comprehensive range from small to large scales
    property var amplitudeScales: [0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, 50.0, 100.0]
    property var amplitudeScaleLabels: ["0.01/div", "0.02/div", "0.05/div", "0.1/div", "0.2/div", "0.5/div", "1/div", "2/div", "5/div", "10/div", "20/div", "50/div", "100/div"]
    property int currentAmplitudeScaleIndex: 6  // Default to 1/div

    Component.onCompleted: {
        console.log("Simple oscilloscope loaded")
        lastFPSTime = new Date().getTime()
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
                        text: "FPS: " + oscilloscopeRoot.currentFPS.toFixed(1)
                        color: oscilloscopeRoot.currentFPS >= 25 ? "#00ff00" : 
                               oscilloscopeRoot.currentFPS >= 15 ? "#ffff00" : "#ff0000"
                        font.pointSize: 8
                        font.bold: true
                    }
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
                        oscilloscopeChart.series("CH1").clear()
                        oscilloscopeChart.series("CH2").clear()
                        oscilloscopeChart.series("CH3").clear()
                        oscilloscopeChart.series("CH4").clear()
                        
                        // Reset timer
                        demoTimer.time = 0
                        
                        // Reset FPS counters
                        oscilloscopeRoot.frameCount = 0
                        oscilloscopeRoot.currentFPS = 0
                        oscilloscopeRoot.lastFPSTime = new Date().getTime()
                        
                        // Reset time axis to initial state
                        var currentTimeScale = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex]
                        var timeWindow = currentTimeScale * 10
                        oscilloscopeChart.axisX().min = 0
                        oscilloscopeChart.axisX().max = timeWindow
                        
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
                                checked: oscilloscopeRoot.channelEnabled[index]
                                
                                onCheckedChanged: {
                                    var newChannelEnabled = oscilloscopeRoot.channelEnabled.slice()
                                    newChannelEnabled[index] = checked
                                    oscilloscopeRoot.channelEnabled = newChannelEnabled
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

                // Time Scale Controls
                Text {
                    text: "TIME SCALE"
                    color: "#00aaff"
                    font.pointSize: 9
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ComboBox {
                    id: timeScaleCombo
                    width: parent.width
                    height: 30
                    model: oscilloscopeRoot.timeScaleLabels
                    currentIndex: oscilloscopeRoot.currentTimeScaleIndex
                    
                    onCurrentIndexChanged: {
                        oscilloscopeRoot.currentTimeScaleIndex = currentIndex
                        console.log("Time scale changed to:", oscilloscopeRoot.timeScaleLabels[currentIndex])
                    }
                    
                    background: Rectangle {
                        color: timeScaleCombo.down ? "#404040" : "#2a2a2a"
                        border.color: timeScaleCombo.activeFocus ? "#00aaff" : "#555555"
                        border.width: 1
                        radius: 4
                    }
                    
                    contentItem: Text {
                        text: timeScaleCombo.displayText
                        color: "#ffffff"
                        font.pointSize: 8
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 8
                        rightPadding: 8
                    }
                    
                    indicator: Text {
                        x: timeScaleCombo.width - width - 8
                        y: timeScaleCombo.height / 2 - height / 2
                        text: "▼"
                        color: "#00aaff"
                        font.pointSize: 8
                    }
                    
                    popup: Popup {
                        y: timeScaleCombo.height
                        width: timeScaleCombo.width
                        height: Math.min(200, timeScaleCombo.model.length * 25 + 2)
                        padding: 1
                        
                        contentItem: ListView {
                            anchors.fill: parent
                            model: timeScaleCombo.delegateModel
                            currentIndex: timeScaleCombo.highlightedIndex
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
                        width: timeScaleCombo.width
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
                max: oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex] * 10
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"
                titleText: "Time (" + oscilloscopeRoot.timeScaleLabels[oscilloscopeRoot.currentTimeScaleIndex] + ")"
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
            
            // High-performance timer for 30 FPS updates
            Timer {
                id: demoTimer
                interval: Math.round(1000 / oscilloscopeRoot.targetFPS)  // 33.33ms = 30 FPS
                running: oscilloscopeRoot.isRunning
                repeat: true
                property real time: 0
                property real lastTime: 0
                
                onTriggered: {
                    var currentTime = new Date().getTime()
                    var deltaTime = interval / 1000.0  // Convert to seconds
                    time += deltaTime
                    
                    // Calculate FPS
                    oscilloscopeRoot.frameCount++
                    if (currentTime - oscilloscopeRoot.lastFPSTime >= 1000) { // Update FPS every second
                        oscilloscopeRoot.currentFPS = oscilloscopeRoot.frameCount * 1000 / (currentTime - oscilloscopeRoot.lastFPSTime)
                        oscilloscopeRoot.frameCount = 0
                        oscilloscopeRoot.lastFPSTime = currentTime
                    }
                    
                    var channels = [channel1, channel2, channel3, channel4]
                    var currentTimeScale = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex]
                    var currentAmplitudeScale = oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex]
                    var timeWindow = currentTimeScale * 10
                    
                    // Generate simple sine waves for each channel
                    for (var ch = 0; ch < 4; ch++) {
                        if (!oscilloscopeRoot.channelEnabled[ch]) continue
                        
                        var frequency = (ch + 1) * 0.5  // Different frequencies
                        var amplitude = currentAmplitudeScale * (ch + 1) * 0.8  // Scale amplitude to current setting
                        var value = amplitude * Math.sin(2 * Math.PI * frequency * time)
                        
                        channels[ch].append(time, value)
                        
                        // Optimized point management for better performance
                        var maxPoints = Math.max(100, Math.min(500, timeWindow * oscilloscopeRoot.targetFPS))
                        if (channels[ch].count > maxPoints) {
                            channels[ch].removePoints(0, channels[ch].count - maxPoints)
                        }
                    }
                    
                    // Auto-scale time axis to show scrolling window based on current time scale
                    if (time > timeWindow) {
                        timeAxis.min = time - timeWindow
                        timeAxis.max = time
                    } else {
                        timeAxis.min = 0
                        timeAxis.max = timeWindow
                    }
                }
            }
        }
    }
}