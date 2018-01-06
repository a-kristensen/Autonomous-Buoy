import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Item {
    width: 1280
    height: 720
    property alias btnGetMotorGainD: btnGetMotorGainD
    property alias btnSetMotorGainD: btnSetMotorGainD
    property alias btnGetMotorGainI: btnGetMotorGainI
    property alias btnSetMotorGainI: btnSetMotorGainI
    property alias btnGetMotorGainP: btnGetMotorGainP
    property alias btnSetMotorGainP: btnSetMotorGainP
    property alias btnGetCtrlGain4: btnGetCtrlGain4
    property alias btnSetCtrlGain4: btnSetCtrlGain4
    property alias btnGetCtrlGain3: btnGetCtrlGain3
    property alias btnSetCtrlGain3: btnSetCtrlGain3
    property alias btnGetCtrlGain2: btnGetCtrlGain2
    property alias btnSetCtrlGain2: btnSetCtrlGain2
    property alias btnGetCtrlGain1: btnGetCtrlGain1
    property alias btnSetCtrlGain1: btnSetCtrlGain1

    property alias txtFControllerGain1: txtFControllerGain1
    property alias txtFControllerGain2: txtFControllerGain2
    property alias txtFControllerGain3: txtFControllerGain3
    property alias txtFCourserVariation1: txtFCourserVariation1

    property alias txtFMotorCtrlP: txtFMotorCtrlP
    property alias txtFMotorCtrlI: txtFMotorCtrlI
    property alias txtFMotorCtrlD: txtFMotorCtrlD



    property alias swCalibrateController: swCalibrateController
    property alias btnCalibrateMotor: btnCalibrateMotor

    Rectangle {

        id: rectangle
        width: 1280
        height: 720
        color: "#ffffff"
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            color: "#cbc7c7"
            border.width: 2
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20

            Text {
                id: text1
                x: 38
                y: 30
                width: 503
                height: 60
                text: qsTr("Heading controller")
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.VerticalFit
                font.pixelSize: 73
            }

            RowLayout {
                x: 8
                y: 127

                Column {

                    Label {
                        id: label
                        width: 225
                        height: 45
                        text: qsTr("Course - Pgain")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }

                    Label {
                        id: label1
                        width: 200
                        height: 45
                        text: qsTr("Courser - Igain")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }

                    Label {
                        id: label2
                        width: 200
                        height: 45
                        text: qsTr("Tilt - Pgain")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }

                    Label {
                        id: label3
                        width: 200
                        height: 45
                        text: qsTr("Calibration param:")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }
                }

                Column {

                    TextField {
                        id: txtFControllerGain1
                        text: qsTr("")
                        font.pointSize: 20
                    }

                    TextField {
                        id: txtFControllerGain2
                        text: qsTr("")
                        font.pointSize: 20
                    }

                    TextField {
                        id: txtFControllerGain3
                        text: qsTr("")
                        font.pointSize: 20
                    }

                    TextField {
                        id: txtFCourserVariation1
                        font.pointSize: 20
                    }
                }
            }

            Button {
                id: btnSetCtrlGain1
                x: 444
                y: 127
                width: 70
                height: 45
                text: qsTr("Set")
                font.pointSize: 20
            }

            Button {
                id: btnGetCtrlGain1
                x: 520
                y: 127
                width: 70
                height: 45
                text: qsTr("Get")
                font.pointSize: 20
            }

            Switch {
                id: swCalibrateController
                x: 74
                y: 412
                width: 72
                height: 38
                text: qsTr("")
                font.family: "Courier"
                font.weight: Font.ExtraLight
                scale: 2
                spacing: 24
                font.pixelSize: 8
                padding: 0
            }

            Label {
                id: label8
                x: 11
                y: 325
                width: 200
                height: 45
                text: qsTr("Calibration")
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 20
                transformOrigin: Item.Center
            }

            Label {
                id: label9
                x: 11
                y: 376
                width: 57
                height: 27
                text: qsTr("OFF")
                font.pointSize: 16
                transformOrigin: Item.Center
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label10
                x: 154
                y: 376
                width: 57
                height: 27
                text: qsTr("ON")
                font.pointSize: 16
                transformOrigin: Item.Center
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                id: btnSetCtrlGain2
                x: 444
                y: 173
                width: 70
                height: 45
                text: qsTr("Set")
                font.pointSize: 20
            }

            Button {
                id: btnGetCtrlGain2
                x: 520
                y: 173
                width: 70
                height: 45
                text: qsTr("Get")
                font.pointSize: 20
            }

            Button {
                id: btnSetCtrlGain3
                x: 444
                y: 219
                width: 70
                height: 45
                text: qsTr("Set")
                font.pointSize: 20
            }

            Button {
                id: btnGetCtrlGain3
                x: 520
                y: 219
                width: 70
                height: 45
                text: qsTr("Get")
                font.pointSize: 20
            }

            Button {
                id: btnSetCtrlGain4
                x: 444
                y: 262
                width: 70
                height: 45
                text: qsTr("Set")
                font.pointSize: 20
            }

            Button {
                id: btnGetCtrlGain4
                x: 520
                y: 262
                width: 70
                height: 45
                text: qsTr("Get")
                font.pointSize: 20
            }
        }

        Rectangle {
            id: rectangle2
            color: "#cbc7c7"
            border.width: 2
            border.color: "#040404"
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20

            Text {
                id: text2
                x: 53
                y: 30
                width: 503
                height: 60
                text: qsTr("Motor controller")
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.VerticalFit
                font.pixelSize: 73
            }

            RowLayout {
                x: 8
                y: 125
                Column {
                    Label {
                        id: label5
                        width: 225
                        height: 45
                        text: qsTr("Controller gain P:")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }

                    Label {
                        id: label6
                        width: 200
                        height: 45
                        text: qsTr("Controller gain I:")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }

                    Label {
                        id: label7
                        width: 200
                        height: 45
                        text: qsTr("Controller gain D:")
                        transformOrigin: Item.Center
                        font.pointSize: 20
                    }
                }

                Column {
                    TextField {
                        id: txtFMotorCtrlP
                        text: qsTr("")
                        font.pointSize: 20
                    }

                    TextField {
                        id: txtFMotorCtrlI
                        text: qsTr("")
                        font.pointSize: 20
                    }

                    TextField {
                        id: txtFMotorCtrlD
                        text: qsTr("")
                        font.pointSize: 20
                    }
                }
            }

            Button {
                id: btnCalibrateMotor
                x: 238
                y: 278
                width: 200
                height: 45
                text: qsTr("Calibrate")
                font.pointSize: 20
            }

            ColumnLayout {
                x: 444
                y: 120

                RowLayout {

                    Button {
                        id: btnSetMotorGainP
                        text: qsTr("Set")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }

                    Button {
                        id: btnGetMotorGainP
                        text: qsTr("Get")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }
                }

                RowLayout {

                    Button {
                        id: btnSetMotorGainI
                        text: qsTr("Set")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }

                    Button {
                        id: btnGetMotorGainI
                        text: qsTr("Get")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }
                }

                RowLayout {

                    Button {
                        id: btnSetMotorGainD
                        text: qsTr("Set")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }

                    Button {
                        id: btnGetMotorGainD
                        text: qsTr("Get")
                        Layout.preferredHeight: 45
                        Layout.preferredWidth: 70
                        font.pointSize: 20
                    }
                }
            }
        }
    }
}
