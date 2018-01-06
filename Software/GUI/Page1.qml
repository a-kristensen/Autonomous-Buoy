import QtQuick 2.7
import QtLocation 5.3

Item {

    Control {
    id: controlArea
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    }


    Position {
        id: mapContainer
        anchors.left: controlArea.right
        //anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

    }
}
