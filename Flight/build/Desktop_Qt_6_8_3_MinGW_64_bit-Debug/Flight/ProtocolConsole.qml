import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: protocolConsole
    width: 500
    height: 200
    color: "lightyellow"
    border.color: "black"
    border.width: 2
    
    Text {
        anchors.centerIn: parent
        text: "Protocol Console"
        font.pointSize: 16
    }
}