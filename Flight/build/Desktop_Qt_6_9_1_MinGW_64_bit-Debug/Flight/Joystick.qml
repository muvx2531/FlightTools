import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: joystick
    width: 200
    height: 200
    color: "lightgreen"
    border.color: "black"
    border.width: 2
    
    Text {
        anchors.centerIn: parent
        text: "Joystick"
        font.pointSize: 16
    }
}