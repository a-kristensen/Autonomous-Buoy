import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtLocation 5.6
import QtPositioning 5.6
import QtQml 2.0

ApplicationWindow {

    readonly property int cmd_set: 1
    readonly property int cmd_get: 0

    readonly property int id_status: 1
    readonly property int sys_mode: 2



    readonly property int wind_Speed: 10
    readonly property int wind_Direction: 11
    readonly property int wind_Temp: 12

    readonly property int gps_long: 20
    readonly property int gps_lat: 21
    readonly property int gps_SOG: 22
    readonly property int gps_Heading: 23
    readonly property int gps_fix: 24

    readonly property int imu_Roll: 30
    readonly property int imu_Pitch: 31
    readonly property int imu_Yaw: 32

    readonly property int motCtrl_P: 40
    readonly property int motCtrl_I: 41
    readonly property int motCtrl_D: 42
    readonly property int motCtrl_Pos: 43

    readonly property int headCtrl_PM: 50
    readonly property int headCtrl_P: 51
    readonly property int headCtrl_I: 52
    readonly property int headCtrl_SPLong: 53
    readonly property int headCtrl_SPLat: 54
    readonly property int headCtrl_Calibration: 55
    readonly property int headCtrl_Course2: 56


    id: applicationWindow
    visible: true
    width: 1280
    height: 720
    title: qsTr("Autonomeus bouy")

    signal sensorChanged(int id, real value)
    signal gpsPositionChanged(double latitude, double longitude, int fix)
    signal newTargetCoordinate(double latitude,double longitude)
    signal systemUpdate(int id, real value)
    signal sigReboot()
    signal sigDisconnected()

    function sensorChange(id,value)
        {            
            applicationWindow.sensorChanged(id,value)
        }

    function gpsPosition(latitude, longitude ,fix)
        {
            applicationWindow.gpsPositionChanged(latitude, longitude, fix)
        }

    function response(id, value){
            applicationWindow.systemUpdate(id,value)
            lblStatusText.text = "Updated"
    }

    function reboot() {
            applicationWindow.sigReboot()
    }

    function disconnected() {
            applicationWindow.sigDisconnected()
    }

    Rectangle {
        id: statusArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50;
        color: "#cbc7c7"
        border.width: 1
        border.color: "#000000"

        Label {
            id: lblStatus
            width: 50
            height: 18
            text: qsTr("Status:")
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: lblStatusText
            width: 124
            height: 18
            text: qsTr("")
            anchors.left: lblStatus.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: lblUpTime
            width: 200
            height: 18
            text: qsTr("Uptime")
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }




    }

    SwipeView {
        id: swipeView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: statusArea.bottom
        currentIndex: tabBar.currentIndex

        Page1 {

        }

        Page2 {

        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Control")
        }
        TabButton {
            text: qsTr("Settings")
        }
    }

    property date currentDate
    property string dateTimeString

    onSigReboot: {
            currentDate = new Date()
            dateTimeString = currentDate.toLocaleString()
            console.log("Reboot" + dateTimeString)
            lblUpTime.text = "Last Reboot: " + dateTimeString
        }

    onSigDisconnected: {
        lblStatusText.text = "DISCONNECTED"
    }
}
