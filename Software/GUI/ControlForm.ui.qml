import QtQuick 2.4
import QtQuick.Controls 2.2
import QtPositioning 5.9
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.0

Item {
    id: item1
    height: 700
    property alias btnTargetSetLong: btnTargetSetLong
    property alias btnTargetGetLong: btnTargetGetLong
    property alias btnTargetSetLat:  btnTargetSetLat
    property alias btnTargetGetLat:  btnTargetGetLat
    width: 500

    property alias massPosition: massPosition
    property alias connectionIndicator: connectionIndicator
    property alias gpsFixIndicator: gpsFixIndicator
    property alias comPort: comPort

    //Sensors
    property alias labelWindTemp: labelWindTemp
    property alias labelWindDirection: labelWindDirection
    property alias labelWindSpeed: labelWindSpeed
    property alias labelIMURoll: labelIMURoll
    property alias labelIMUPitch: labelIMUPitch
    property alias labelIMUYaw: labelIMUYaw
    property alias labelGPSLongitude: labelGPSLongitude
    property alias labelGPSLatitude: labelGPSLatitude
    property alias labelGPSSpeed: labelGPSSpeed
    property alias labelGPSHeading: labelGPSHeading

    property alias btnConnect: btnConnect
    property alias switchMode: switchMode
    property alias btnCalNorth: btnCalNorth

    property alias labelTargetLongitude: labelTargetLongitude
    property alias labelTargetLatitude: labelTargetLatitude

    property alias showMassPos: showMassPos



        Rectangle {
            id: rectangle
            color: "#cbc7c7"
            //anchors.rightMargin: 20
            //anchors.leftMargin: 20
            //anchors.bottomMargin: 20
            //anchors.topMargin: 20
            x:0
            y:0

            anchors.fill: parent
            border.width: 1
            border.color: "#000000"
            z: 0

            //TextField {
            //    id: comPort
            //    width: 120
            //    height: 25
            //    text: qsTr("Comport: Eg. COM12")
            //    anchors.top: labelconnecton.bottom
            //    anchors.topMargin: 4
            //    anchors.horizontalCenter: labelconnecton.horizontalCenter
            //}

            Slider {
                id: massPosition
                x: 8
                y: 519
                width: 484
                height: 40
                z: 1
                value: 0.5
            }

            StatusIndicator {
                id: connectionIndicator
                x: 217
                y: 397
                width: 26
                height: 25
                color: "#00ff00"
                active: false
            }

            ColumnLayout {
                x: 52
                y: 70
            }

            Label {
                id: labelconnecton
                x: 36
                y: 372
                text: qsTr("Connection")
                font.pixelSize: 17
            }

            Label {
                id: labelMotorSetpoint
                x: 184
                y: 493
                text: qsTr("Mass setpoint")
                font.underline: false
                font.pointSize: 16
            }

            StatusIndicator {
                id: gpsFixIndicator
                x: 213
                y: 206
                width: 36
                height: 36
                color: "#00ff00"
                active: false
            }

            Label {
                id: labelGpsFix1
                x: 148
                y: 214
                text: qsTr("GPS Fix")
                font.pointSize: 12
            }

            Label {
                id: labelWindTemp
                x: 17
                y: 46
                width: 124
                height: 18
                text: qsTr("labelWindTemp")
            }

            Label {
                id: labelWindDirection
                x: 17
                y: 70
                width: 124
                height: 18
                text: qsTr("labelWindDirection")
            }

            Label {
                id: labelWindSpeed
                x: 17
                y: 94
                width: 124
                height: 18
                text: qsTr("labelWindSpeed")
            }

            Label {
                id: labelGPSLongitude
                x: 17
                y: 151
                width: 124
                height: 18
                text: qsTr("labelGPSLongitude")
            }

            Label {
                id: labelGPSLatitude
                x: 17
                y: 175
                width: 124
                height: 18
                text: qsTr("labelGPSLatitude")
            }

            Label {
                id: labelIMURoll
                x: 17
                y: 279
                width: 124
                height: 18
                text: qsTr("labelIMURoll")
            }

            Label {
                id: labelIMUPitch
                x: 17
                y: 303
                width: 124
                height: 18
                text: qsTr("labelIMUPitch")
            }

            Label {
                id: labelIMUYaw
                x: 17
                y: 327
                width: 124
                height: 18
                text: qsTr("labelIMUYaw")
            }

            Text {
                id: text2
                x: 36
                y: 19
                text: qsTr("Windsensor")
                font.pixelSize: 17
            }

            Text {
                id: text3
                x: 61
                y: 124
                text: qsTr("GPS")
                font.pixelSize: 17
            }

            Text {
                id: text4
                x: 61
                y: 252
                text: qsTr("IMU")
                font.pixelSize: 17
            }

            Button {
                id: btnConnect
                x: 139
                y: 396
                width: 63
                height: 26
                text: qsTr("Connect")
            }

            Switch {
                id: switchMode
                x: 17
                y: 456
                width: 70
                height: 34
                text: qsTr("")
                rightPadding: 0
                leftPadding: 0
                font.pointSize: 9
                scale: 1
                bottomPadding: 4
            }

            Label {
                id: lblMode
                x: 17
                y: 437
                text: qsTr("Manuel")
            }

            Label {
                id: lblMode1
                x: 64
                y: 437
                width: 23
                height: 13
                text: qsTr("Auto")
            }

            Label {
                id: labelGPSSpeed
                x: 18
                y: 199
                width: 124
                height: 18
                text: qsTr("labelGPSSpeed")
            }

            Label {
                id: labelGPSHeading
                x: 18
                y: 223
                width: 124
                height: 18
                text: qsTr("labelGPSHeading")
            }

            Label {
                id: labelTargetLongitude
                x: 243
                y: 151
                width: 124
                height: 18
                text: qsTr("labelTargetLongitude")
                horizontalAlignment: Text.AlignLeft
            }

            Label {
                id: labelTargetLatitude
                x: 243
                y: 175
                width: 124
                height: 18
                text: qsTr("labelTargetLatitude")
                horizontalAlignment: Text.AlignLeft
            }

            Text {
                id: text5
                x: 231
                y: 124
                width: 49
                height: 21
                text: qsTr("Target")
                font.pixelSize: 17
            }

            Label {
                id: labelIMURoll3
                x: 186
                y: 151
                width: 51
                height: 18
                text: qsTr("Longitude")
            }

            Label {
                id: labelIMURoll4
                x: 186
                y: 175
                width: 51
                height: 18
                text: qsTr("Latitude")
            }
            Button {
                id: btnTargetSetLong
                x: 377
                y: 150
                width: 62
                height: 18
                text: qsTr("Set")
            }

            Button {
                id: btnTargetGetLong
                x: 315
                y: 150
                width: 62
                height: 18
                text: qsTr("Get")
            }

            Slider {
                id: showMassPos
                x: 8
                y: 598
                width: 484
                height: 40
                font.weight: Font.Normal
                enabled: false
                visible: true
                value: 0.5
            }

            Label {
                id: labelMassPos
                x: 169
                y: 569
                text: qsTr("Mass position")
                font.underline: false
                font.pointSize: 16
            }

            TextInput {
                id: comPort
                x: 13
                y: 402
                width: 125
                height: 16
                text: qsTr("Enter com: E.g COM12")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            Button {
                id: btnTargetGetLat
                x: 315
                y: 175
                width: 62
                height: 18
                text: qsTr("Get")
            }

            Button {
                id: btnTargetSetLat
                x: 377
                y: 175
                width: 62
                height: 18
                text: qsTr("Set")
            }

            Button {
                id: btnCalNorth
                x: 84
                y: 327
                width: 70
                height: 18
                text: qsTr("Set north")
            }
        }
    }
