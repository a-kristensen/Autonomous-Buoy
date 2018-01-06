import QtQuick 2.4

Page2Form {

    //HEADING


    btnGetCtrlGain1 {
        onClicked: { backend.sendCommandFromQML(cmd_get,headCtrl_PM,"0")
        lblStatusText.text = ""
        }

    }

    btnSetCtrlGain1 {
        onClicked:{ backend.sendCommandFromQML(cmd_set,headCtrl_PM,txtFControllerGain1.text)
        lblStatusText.text = ""
         }

    }

    btnGetCtrlGain2 {
        onClicked:{ backend.sendCommandFromQML(cmd_get,headCtrl_P,"0")
        lblStatusText.text = ""
        }

    }

    btnSetCtrlGain2 {
        onClicked:{ backend.sendCommandFromQML(cmd_set,headCtrl_P,txtFControllerGain2.text)
        lblStatusText.text = ""
        }

    }

    btnGetCtrlGain3 {
        onClicked: {backend.sendCommandFromQML(cmd_get,headCtrl_I,"0")
            lblStatusText.text = ""}

    }

    btnSetCtrlGain3 {
        onClicked:{ backend.sendCommandFromQML(cmd_set,headCtrl_I,txtFControllerGain3.text)
            lblStatusText.text = ""}

    }

    btnGetCtrlGain4 {
        onClicked:{ backend.sendCommandFromQML(cmd_get,headCtrl_Calibration,"0")
            lblStatusText.text = ""}

    }

    btnSetCtrlGain4 {
        onClicked:{ backend.sendCommandFromQML(cmd_set,headCtrl_Calibration,txtFCourserVariation1.text)
            lblStatusText.text = ""}

    }


    swCalibrateController {
        onPressed: {
            backend.setCalModeController(!swCalibrateController.checked)
            lblStatusText.text = ""

        }
    }


    //MOTOR

    btnGetMotorGainP {
        onClicked: {backend.sendCommandFromQML(cmd_get,motCtrl_P,"0")
            lblStatusText.text = ""
        }

    }

    btnSetMotorGainP {
        onClicked: {backend.sendCommandFromQML(cmd_set,motCtrl_P,txtFMotorCtrlP.text)
            lblStatusText.text = ""
        }

    }

    btnGetMotorGainI {
        onClicked:{ backend.sendCommandFromQML(cmd_get,motCtrl_I,"0")
            lblStatusText.text = ""
        }

    }

    btnSetMotorGainI {
        onClicked: {backend.sendCommandFromQML(cmd_set,motCtrl_I,txtFMotorCtrlI.text)
            lblStatusText.text = ""}

    }

    btnGetMotorGainD {
        onClicked:{ backend.sendCommandFromQML(cmd_get,motCtrl_D,"0")
            lblStatusText.text = ""}

    }

    btnSetMotorGainD {
        onClicked: {backend.sendCommandFromQML(cmd_set,motCtrl_D,txtFMotorCtrlD.text)
            lblStatusText.text = ""}

    }

    btnCalibrateMotor {
        onPressed: {
            backend.setCalModeMotor(1)
            lblStatusText.text = ""
        }
    }

    Connections {
        target:applicationWindow

        onSystemUpdate:{

            switch(id){
            case headCtrl_PM:
                txtFControllerGain1.text = value.toFixed(6)
            break

            case headCtrl_P:
                txtFControllerGain2.text = value.toFixed(6)
            break

            case headCtrl_I:
                txtFControllerGain3.text = value.toFixed(6)
            break

            case headCtrl_Calibration:
                txtFCourserVariation1.text = value.toFixed(3)
            break

            case motCtrl_P:
                txtFMotorCtrlP.text = value.toFixed(3)
            break

            case motCtrl_I:
                txtFMotorCtrlI.text = value.toFixed(3)
            break

            case motCtrl_D:
                txtFMotorCtrlD.text = value.toFixed(3)
            break

            }
        }


    }

}
