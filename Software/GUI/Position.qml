import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle
{
    border.width: 1
    border.color: 'black'
    Plugin {
              id: mapPlugin
              name: "osm" // "mapboxgl", "esri", ...
           }

    Map {
        id: map
              anchors.fill: parent
              plugin: mapPlugin
              //center: QtPositioning.coordinate(56.404830, 9.549232)
              center {
                  latitude: 54.9133376
                  longitude: 9.780911
              }

              zoomLevel: 16

              MapQuickItem {
                  id: buoy
                  sourceItem: Rectangle { width: 14; height: 14; color: "#e41e25"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                  coordinate {
                      latitude: 54.9133376
                      longitude: 9.780911
                  }
                  opacity: 1.0
                  anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
              }

              MapQuickItem {
                  id: target
                  sourceItem: Rectangle { width: 14; height: 14; color: "#0000ff"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
                  coordinate {
                      latitude: 54.9133376
                      longitude: 9.780911
                  }
                  opacity: 0
                  anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
              }

              MapQuickItem {
                  sourceItem: Text{
                      text: "Bouy"
                      color:"#242424"
                      font.bold: true
                      styleColor: "#ECECEC"
                      style: Text.Outline
                  }
                  coordinate: buoy.coordinate
                  anchorPoint: Qt.point(-buoy.sourceItem.width * 0.5,buoy.sourceItem.height * 1.5)
              }

              MapQuickItem {
                  sourceItem: Text{
                      text: "Target"
                      color:"#242424"
                      font.bold: true
                      styleColor: "#ECECEC"
                      style: Text.Outline
                  }
                  coordinate: target.coordinate
                  anchorPoint: Qt.point(-target.sourceItem.width * 0.5,target.sourceItem.height * 1.5)
              }

              Connections {
                  target:applicationWindow

                  onSystemUpdate: {

                      switch(id){
                      case headCtrl_SPLat:
                          target.coordinate.latitude = value
                          target.opacity = 1.0
                      break

                      case headCtrl_SPLong:
                          target.coordinate.longitude = value
                          target.opacity = 1.0
                      }
                  }


                  onGpsPositionChanged: {
                      if(fix == 1){
                      buoy.coordinate.latitude = latitude
                      buoy.coordinate.longitude = longitude
                      }
                  }
               }

              MouseArea{
                  anchors.fill: parent
                  acceptedButtons: Qt.LeftButton | Qt.RightButton
                  onPressed: {
                    if(mouse.button == Qt.RightButton) {

                            target.coordinate.latitude = map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude
                            target.coordinate.longitude = map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude
                            target.opacity = 1.0
                            applicationWindow.newTargetCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)

                    }

                  }
               }
    }


}

