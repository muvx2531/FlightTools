import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: pidAdjustmentPanel
    width: 300
    height: 400
    color: "lightblue"
    border.color: "black"
    border.width: 2
    
    Text {
        anchors.centerIn: parent
        text: "PID Adjustment Panel"
        font.pointSize: 16
    }
}