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

    // C++ Backend Interface Properties (to be connected to C++ backend)
    property var oscilloscopeData: null
    property bool isRunning: false
    property bool needsClear: false
    
    // Time scale options: 0.1s/div, 0.5s/div, 1s/div, 10s/div
    property var timeScales: [0.1, 0.5, 1.0, 10.0]
    property var timeScaleLabels: ["0.1s/div", "0.5s/div", "1s/div", "10s/div"]
    property int currentTimeScaleIndex: 2  // Default to 1s/div
    
    // Amplitude scale options: 0.1, 0.2, 0.5, 1, 2, 5, 10 units per division
    property var amplitudeScales: [0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0]
    property var amplitudeScaleLabels: ["0.1/div", "0.2/div", "0.5/div", "1/div", "2/div", "5/div", "10/div"]
    property int currentAmplitudeScaleIndex: 3
    
    // Channel properties
    property var channelEnabled: [true, true, true, true]
    property var channelColors: ["#00ff00", "#ffff00", "#ff6600", "#ff0088"]
    property var channelLabels: ["CH1", "CH2", "CH3", "CH4"]

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

                    // Title
                    Text {
                        text: "OSCILLOSCOPE"
                        color: "#00aaff"
                        font.pointSize: 10
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#404040"
                    }

                    // Start/Stop and Clear buttons
                    Column {
                        width: parent.width
                        spacing: 6

                        Text {
                            text: "ACQUISITION"
                            color: "#cccccc"
                            font.pointSize: 9
                            font.bold: true
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
                                // Signal to C++ backend
                                if (oscilloscopeRoot.oscilloscopeData) {
                                    oscilloscopeRoot.oscilloscopeData.setRunning(oscilloscopeRoot.isRunning)
                                }
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
                                
                                // Animation for visual feedback
                                Behavior on color {
                                    ColorAnimation { duration: 100 }
                                }
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
                                oscilloscopeRoot.needsClear = true
                                // Clear all chart series immediately
                                oscilloscopeChart.channel1.clear()
                                oscilloscopeChart.channel2.clear()
                                oscilloscopeChart.channel3.clear()
                                oscilloscopeChart.channel4.clear()
                                // Signal to C++ backend
                                if (oscilloscopeRoot.oscilloscopeData) {
                                    oscilloscopeRoot.oscilloscopeData.clearBuffer()
                                }
                                console.log("Oscilloscope cleared - all channels reset")
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#404040"
                    }

                    // Time Scale Controls
                    Column {
                        width: parent.width
                        spacing: 6

                        Text {
                            text: "TIME SCALE"
                            color: "#cccccc"
                            font.pointSize: 9
                            font.bold: true
                        }

                        ComboBox {
                            id: timeScaleCombo
                            width: parent.width
                            height: 30
                            currentIndex: oscilloscopeRoot.currentTimeScaleIndex
                            
                            model: oscilloscopeRoot.timeScaleLabels
                            
                            background: Rectangle {
                                color: "#333333"
                                border.color: "#555555"
                                border.width: 1
                                radius: 4
                            }
                            
                            contentItem: Text {
                                text: timeScaleCombo.displayText
                                color: "#cccccc"
                                font.pointSize: 9
                                verticalAlignment: Text.AlignVCenter
                                leftPadding: 8
                            }
                            
                            onCurrentIndexChanged: {
                                oscilloscopeRoot.currentTimeScaleIndex = currentIndex
                            }
                        }
                    }

                    // Amplitude Scale Controls
                    Column {
                        width: parent.width
                        spacing: 6

                        Text {
                            text: "AMPLITUDE SCALE"
                            color: "#cccccc"
                            font.pointSize: 9
                            font.bold: true
                        }

                        ComboBox {
                            id: amplitudeScaleCombo
                            width: parent.width
                            height: 30
                            currentIndex: oscilloscopeRoot.currentAmplitudeScaleIndex
                            
                            model: oscilloscopeRoot.amplitudeScaleLabels
                            
                            background: Rectangle {
                                color: "#333333"
                                border.color: "#555555"
                                border.width: 1
                                radius: 4
                            }
                            
                            contentItem: Text {
                                text: amplitudeScaleCombo.displayText
                                color: "#cccccc"
                                font.pointSize: 9
                                verticalAlignment: Text.AlignVCenter
                                leftPadding: 8
                            }
                            
                            onCurrentIndexChanged: {
                                oscilloscopeRoot.currentAmplitudeScaleIndex = currentIndex
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#404040"
                    }

                    // Channel Controls
                    Column {
                        width: parent.width
                        spacing: 6

                        Text {
                            text: "CHANNELS"
                            color: "#cccccc"
                            font.pointSize: 9
                            font.bold: true
                        }

                        Repeater {
                            model: 4
                            
                            Row {
                                width: parent.width
                                spacing: 8
                                
                                CheckBox {
                                    id: channelCheckBox
                                    checked: oscilloscopeRoot.channelEnabled[index]
                                    
                                    indicator: Rectangle {
                                        implicitWidth: 18
                                        implicitHeight: 18
                                        radius: 3
                                        border.color: oscilloscopeRoot.channelColors[index]
                                        border.width: 2
                                        color: channelCheckBox.checked ? oscilloscopeRoot.channelColors[index] : "transparent"
                                        
                                        Rectangle {
                                            width: 8
                                            height: 8
                                            radius: 2
                                            anchors.centerIn: parent
                                            color: "white"
                                            visible: channelCheckBox.checked
                                        }
                                    }
                                    
                                    onCheckedChanged: {
                                        let newEnabled = oscilloscopeRoot.channelEnabled.slice()
                                        newEnabled[index] = checked
                                        oscilloscopeRoot.channelEnabled = newEnabled
                                    }
                                }
                                
                                Text {
                                    text: oscilloscopeRoot.channelLabels[index]
                                    color: oscilloscopeRoot.channelColors[index]
                                    font.pointSize: 9
                                    font.bold: true
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                }
        }

        // Professional Oscilloscope ChartView (following FlightSim pattern)
        ChartView {
            id: oscilloscopeChart
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            // Appearance (matching successful FlightSim project)
            theme: ChartView.ChartThemeDark
            backgroundColor: "#000000"
            plotAreaColor: "#000a0a"  // Very dark green like CRT phosphor
            antialiasing: true
            animationOptions: ChartView.NoAnimation  // Critical for real-time performance
            legend.visible: false
            
            // Time axis (X)
            ValueAxis {
                id: timeAxis
                min: 0
                max: oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex] * 10
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"  // Brighter green grid for better visibility
                minorGridVisible: true
                minorGridLineColor: "#004400"  // Minor grid lines for precision
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"  // Bright green for better visibility
                labelsFont.family: "Arial"
                labelsFont.pixelSize: 12
                labelsFont.bold: true
                titleText: "Time (s)"
                titleFont.family: "Arial"
                titleFont.pixelSize: 14
                titleFont.bold: true
                titleBrush: Qt.rgba(0, 1, 0, 1)  // Bright green
            }
            
            // Amplitude axis (Y)
            ValueAxis {
                id: amplitudeAxis
                min: -oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 5
                max: oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 5
                tickCount: 11
                gridVisible: true
                gridLineColor: "#00aa00"  // Brighter green grid for better visibility
                minorGridVisible: true
                minorGridLineColor: "#004400"  // Minor grid lines for precision
                lineVisible: true
                labelsVisible: true
                labelsColor: "#00ff00"  // Bright green for better visibility
                labelsFont.family: "Arial"
                labelsFont.pixelSize: 12
                labelsFont.bold: true
                titleText: "Amplitude"
                titleFont.family: "Arial"
                titleFont.pixelSize: 14
                titleFont.bold: true
                titleBrush: Qt.rgba(0, 1, 0, 1)  // Bright green
            }
            
            // Channel 1 - Roll
            LineSeries {
                id: channel1
                name: "CH1"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[0]  // "#00ff00"
                width: 2
                visible: oscilloscopeRoot.channelEnabled[0]
                useOpenGL: openGLSupported  // Hardware acceleration
            }
            
            // Channel 2 - Pitch
            LineSeries {
                id: channel2
                name: "CH2"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[1]  // "#ffff00"
                width: 2
                visible: oscilloscopeRoot.channelEnabled[1]
                useOpenGL: openGLSupported
            }
            
            // Channel 3 - Yaw
            LineSeries {
                id: channel3
                name: "CH3"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[2]  // "#ff6600"
                width: 2
                visible: oscilloscopeRoot.channelEnabled[2]
                useOpenGL: openGLSupported
            }
            
            // Channel 4 - Altitude
            LineSeries {
                id: channel4
                name: "CH4"
                axisX: timeAxis
                axisY: amplitudeAxis
                color: oscilloscopeRoot.channelColors[3]  // "#ff0088"
                width: 2
                visible: oscilloscopeRoot.channelEnabled[3]
                useOpenGL: openGLSupported
            }
            
            // Real-time data generation timer (following FlightSim pattern)
            Timer {
                id: dataTimer
                interval: 1 / 30 * 1000  // 30 FPS like FlightSim
                running: oscilloscopeRoot.isRunning
                repeat: true
                onTriggered: {
                    updateSampleData()
                }
            }
            
            // Sample data generation function (following FlightSim pattern)
            function updateSampleData() {
                var currentTime = new Date().getTime() / 1000
                var timeRange = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex] * 10
                var amplitudeRange = oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 3
                
                var channels = [channel1, channel2, channel3, channel4]
                
                for (var ch = 0; ch < 4; ch++) {
                    if (!oscilloscopeRoot.channelEnabled[ch]) continue
                    
                    // Clear and regenerate data (like FlightSim batch update)
                    channels[ch].clear()
                    
                    // Generate oscilloscope waveform
                    for (var i = 0; i <= 100; i++) {
                        var time = (timeRange * i) / 100
                        var phase = ch * Math.PI / 2
                        var frequency = (ch + 1) * 2 * Math.PI / timeRange
                        var amplitude = amplitudeRange * Math.sin(frequency * time + currentTime + phase)
                        
                        channels[ch].append(time, amplitude)
                    }
                }
            }
            
            // Update axes when scale changes (following FlightSim pattern)
            Connections {
                target: oscilloscopeRoot
                function onCurrentTimeScaleIndexChanged() {
                    timeAxis.max = oscilloscopeRoot.timeScales[oscilloscopeRoot.currentTimeScaleIndex] * 10
                }
                function onCurrentAmplitudeScaleIndexChanged() {
                    var range = oscilloscopeRoot.amplitudeScales[oscilloscopeRoot.currentAmplitudeScaleIndex] * 5
                    amplitudeAxis.min = -range
                    amplitudeAxis.max = range
                }
            }
            
            // Status overlay
            Rectangle {
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.margins: 8
                width: 120
                height: 60
                color: "#2a2a2a"
                border.color: "#404040"
                border.width: 1
                radius: 4
                opacity: 0.9

                Column {
                    anchors.centerIn: parent
                    spacing: 4

                    Text {
                        text: oscilloscopeRoot.isRunning ? "● RUNNING" : "⏸ STOPPED"
                        color: oscilloscopeRoot.isRunning ? "#00ff00" : "#ff4444"
                        font.pointSize: 9
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: "30 FPS"
                        color: "#cccccc"
                        font.pointSize: 8
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: oscilloscopeRoot.timeScaleLabels[oscilloscopeRoot.currentTimeScaleIndex] + " | " + 
                              oscilloscopeRoot.amplitudeScaleLabels[oscilloscopeRoot.currentAmplitudeScaleIndex]
                        color: "#aaaaaa"
                        font.pointSize: 7
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }

    // C++ Backend API Interface
    // These functions should be connected to your C++ backend
    function connectToBackend(backendObject) {
        oscilloscopeData = backendObject
        // Connect signals from C++ backend for real-time data updates
    }
    
    function updateWaveformData(channelData) {
        // This function will be called by C++ backend to update waveform data
        // channelData should be an array of 4 arrays, each containing time-value pairs
        var channels = [oscilloscopeChart.channel1, oscilloscopeChart.channel2,
                       oscilloscopeChart.channel3, oscilloscopeChart.channel4]
        
        for (var ch = 0; ch < 4; ch++) {
            if (!oscilloscopeRoot.channelEnabled[ch] || !channelData[ch]) continue
            
            channels[ch].clear()
            for (var i = 0; i < channelData[ch].length; i++) {
                channels[ch].append(channelData[ch][i].time, channelData[ch][i].value)
            }
        }
    }
}
