import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: flightInstument
    width: 250
    height: 250
    color: "lightpink"
    border.color: "black"
    border.width: 2
    
    Text {
        anchors.centerIn: parent
        text: "Flight Instrument"
        font.pointSize: 16
    }
}