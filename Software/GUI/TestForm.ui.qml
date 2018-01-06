import QtQuick 2.4
import QtQuick.Controls 2.2
import QtPositioning 5.9
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0

Item {
    width: 400
    height: 700
    //anchors.bottom: parent.bottom
    //anchors.top: parent.top

    Rectangle {
        id: rectangle
        color: "#cbc7c7"
        x: 0
        y: 0
        anchors.fill: parent
        border.width: 1
        border.color: "#000000"

        TextField {
            id: comPort
            x: 51
            y: 159
            width: 120
            height: 25
            text: qsTr("Comport: Eg. COM12")
        }

        Slider {
            id: massPosition
            x: 8
            y: 395
            width: 368
            height: 40
            z: 1
            value: 0.5
        }

        StatusIndicator {
            id: connectionIndicator
            x: 237
            y: 165
            width: 26
            height: 25
            color: "#00ff00"
            active: false
        }
    }
}
