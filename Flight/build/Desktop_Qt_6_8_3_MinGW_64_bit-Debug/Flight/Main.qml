import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: mainWindow
    width: 1600
    height: 1000
    visible: true
    title: "Flight Control System - Professional Dashboard"
    minimumWidth: 1200
    minimumHeight: 800

    Rectangle {
        id: mainContainer
        anchors.fill: parent
        color: "#1a1a1a"

        // Main Grid Layout - Maximized Oscilloscope for Data Analysis
        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.margins: 15
            columns: 4
            rows: 3
            columnSpacing: 12
            rowSpacing: 12

            // ROW 1 - COMPACT FLIGHT MONITORING (Reduced Heights)
            // Column 1-2: LARGE Flight Instruments (2x size, spans 2 columns)
            FlightInstument {
                id: flightInstruments
                Layout.row: 0
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.preferredWidth: 600
                Layout.preferredHeight: 220
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            }

            // Column 3: Compact 3D Orientation Display
            Plot3DOrientation {
                id: orientationDisplay
                Layout.row: 0
                Layout.column: 2
                Layout.preferredWidth: 250
                Layout.preferredHeight: 220
                Layout.alignment: Qt.AlignTop | Qt.AlignCenter
            }

            // Column 4: Compact Manual Flight Controls
            Rectangle {
                id: controlSection
                Layout.row: 0
                Layout.column: 3
                Layout.preferredWidth: 250
                Layout.preferredHeight: 220
                Layout.alignment: Qt.AlignTop | Qt.AlignRight
                color: "#2a2a2a"
                border.color: "#404040"
                border.width: 2
                radius: 8

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Text {
                        text: "MANUAL CONTROL"
                        color: "#00ff88"
                        font.pointSize: 10
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Row {
                        spacing: 15
                        anchors.horizontalCenter: parent.horizontalCenter

                        Column {
                            spacing: 4
                            Joystick {
                                id: leftStick
                                width: 45
                                height: 45
                            }
                            Text {
                                text: "THROT/YAW"
                                color: "#cccccc"
                                font.pointSize: 7
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Column {
                            spacing: 4
                            Joystick {
                                id: rightStick
                                width: 45
                                height: 45
                            }
                            Text {
                                text: "PITCH/ROLL"
                                color: "#cccccc"
                                font.pointSize: 7
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }

                    Column {
                        spacing: 8
                        anchors.horizontalCenter: parent.horizontalCenter

                        Rectangle {
                            width: 120
                            height: 25
                            color: "#ff4444"
                            radius: 4
                            anchors.horizontalCenter: parent.horizontalCenter

                            Text {
                                anchors.centerIn: parent
                                text: "EMERGENCY"
                                color: "white"
                                font.pointSize: 8
                                font.bold: true
                            }
                        }

                        Rectangle {
                            width: 120
                            height: 22
                            color: "#ffaa00"
                            radius: 4
                            anchors.horizontalCenter: parent.horizontalCenter

                            Text {
                                anchors.centerIn: parent
                                text: "AUTO LAND"
                                color: "black"
                                font.pointSize: 7
                                font.bold: true
                            }
                        }
                    }
                }
            }

            // ROW 2 - PID TUNING SECTION WITH MASSIVE OSCILLOSCOPE
            // Column 1: PID Panel (equal height to oscilloscope)
            PIDadjustmentPanel {
                id: pidPanel
                Layout.row: 1
                Layout.column: 0
                Layout.preferredWidth: 300
                Layout.preferredHeight: 480
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter | Qt.AlignLeft
            }

            // Column 2-4: MASSIVE Realtime Oscilloscope (spans 3 columns!)
            RealtimeOscilloscope {
                id: oscilloscope
                Layout.row: 1
                Layout.column: 1
                Layout.columnSpan: 3
                Layout.preferredWidth: 900
                Layout.preferredHeight: 480
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
            }

            // ROW 3 - COMMUNICATION (Reduced Height)
            // Column 1-4: Compact Protocol Console
            ProtocolConsole {
                id: protocolConsole
                Layout.row: 2
                Layout.column: 0
                Layout.columnSpan: 4
                Layout.preferredHeight: 150
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
            }
        }

        // Top Status Bar - Always visible
        Rectangle {
            id: topStatusBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 35
            color: "#333333"
            border.color: "#555555"
            border.width: 1

            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 15

                Text {
                    text: "FLIGHT STATUS:"
                    color: "#cccccc"
                    font.pointSize: 10
                    font.bold: true
                }

                Rectangle {
                    width: 12
                    height: 12
                    radius: 6
                    color: "#ff4444"
                }

                Text {
                    text: "DISCONNECTED"
                    color: "#ff6666"
                    font.pointSize: 10
                    font.bold: true
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "BATTERY: ---%"
                    color: "#cccccc"
                    font.pointSize: 10
                }

                Text {
                    text: "ALTITUDE: -- m"
                    color: "#cccccc"
                    font.pointSize: 10
                }

                Text {
                    text: "SPEED: -- m/s"
                    color: "#cccccc"
                    font.pointSize: 10
                }

                Text {
                    text: new Date().toLocaleTimeString()
                    color: "#88ff88"
                    font.pointSize: 10

                    Timer {
                        interval: 1000
                        running: true
                        repeat: true
                        onTriggered: parent.text = new Date().toLocaleTimeString()
                    }
                }
            }
        }
    }
}


