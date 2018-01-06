import QtQuick 2.4

ControlForm {
    property string port



    massPosition {
        onValueChanged:
        {
            //console.log(massPosition.value)
            backend.setMotorPosition(massPosition.value)
            //showMassPos.value = massPosition.value
        }
    }

    Connections {
        target:applicationWindow
        property real gpslong
        property real gpslat
        property int  gpsfix: 0

        onSensorChanged: {

           switch(id){

           case wind_Temp:
                labelWindTemp.text = "Temprature: " + value.toFixed(1) + " °C"
           break

           case wind_Direction:
                labelWindDirection.text = "Directiuon: " + value.toFixed(1) + "°"
           break

           case wind_Speed:
                labelWindSpeed.text = "Speed: " + value.toFixed(2) + "knots"
           break

           case gps_long:
                labelGPSLongitude.text = "Longiude: " + value.toFixed(7) + "°"
                gpslong = value
                applicationWindow.gpsPosition(gpslat,gpslong,gpsfix)
           break

           case gps_lat:
                gpslat = value
                labelGPSLatitude.text = "Latitude: " + value.toFixed(7) + "°"
                applicationWindow.gpsPosition(gpslat,gpslong,gpsfix)
           break

           case gps_SOG:
                labelGPSSpeed.text = "SOG: " + value.toFixed(6) + "knots"
           break

           case gps_Heading:
                labelGPSHeading.text ="COG: " + value.toFixed(2) + "°"
           break

           case gps_fix:
                if(value > 0){
                    gpsFixIndicator.active = 1
                    gpsfix = 1
                }else{
                    gpsFixIndicator.active = 0
                    gpsfix = 0
                }
           break

           case motCtrl_Pos:
               //console.log(value.toString())
                showMassPos.value = value/200
           break;

           case imu_Roll:
                labelIMURoll.text = "Roll: " + value.toFixed(1) + "°"
           break

           case imu_Pitch:
                labelIMUPitch.text = "Pitch: " + value.toFixed(1) + "°"
           break

           case imu_Yaw:
                labelIMUYaw.text = "Yaw: " + value.toFixed(1) + "°"
           break
           }
                if(connectionIndicator.active == 0) {
                    lblStatusText.text = ""
                }

                connectionIndicator.active = 1


        }

        onSigDisconnected: {

            gpsFixIndicator.active = 0
            connectionIndicator.active = 0


        }

        onNewTargetCoordinate: {
            labelTargetLatitude.text = latitude.toFixed(7)
            labelTargetLongitude.text = longitude.toFixed(7)

        }


        onSystemUpdate: {

            switch(id){
            case headCtrl_SPLat:
                labelTargetLatitude.text = value.toFixed(7)
            break

            case headCtrl_SPLong:
                labelTargetLongitude.text = value.toFixed(7)
            }

        }

     }

    btnTargetGetLong {
        onClicked: {
            backend.sendCommandFromQML( cmd_get, headCtrl_SPLong,"0")
            lblStatusText.text = ""
        }

    }

    btnTargetSetLong {
        onClicked: {
            backend.sendCommandFromQML(cmd_set, headCtrl_SPLong ,labelTargetLongitude.text)
            lblStatusText.text = ""
        }

    }

    btnTargetGetLat {
        onClicked: {
            backend.sendCommandFromQML(cmd_get, headCtrl_SPLat ,"0")
            lblStatusText.text = ""
        }

    }

    btnTargetSetLat {
        onClicked: {
            backend.sendCommandFromQML(cmd_set, headCtrl_SPLat ,labelTargetLatitude.text)
            lblStatusText.text = ""
        }

    }

    btnConnect {

        onClicked: {
        backend.connectBouy(port)
        }
    }

    btnCalNorth {
        onClicked: {
            backend.setCalNorth()
            lblStatusText.text = ""
        }
    }

    comPort {
        onTextChanged: port = comPort.text
    }

    switchMode{
        onPressed: {
            backend.setMode(!switchMode.checked)
            massPosition.enabled = switchMode.checked
            lblStatusText.text = ""
        }
    }

    labelTargetLatitude.text: "54.9133376"
    labelTargetLongitude.text:   "9.780911"

}
