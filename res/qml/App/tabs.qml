import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  height: 30;

  Row {
    anchors.left: parent.left;
    anchors.bottom: parent.bottom;
    anchors.right: parent.right;

    Repeater {
      model: App.document.files;

      Rectangle {
        anchors.bottom: parent.bottom;
        height: content.height + 10;
        width: content.width + 20;
        color: "#181A1F"
        border.color: "#282C34";
        radius: 4;
        anchors.bottomMargin: -2;

        MouseArea {
          id: ma;

          hoverEnabled: true;
          anchors.fill: parent;

          onClicked: {
            modelData.select();
          }
        }

        Row {
          id: content;

          spacing: 10;
          anchors.centerIn: parent;

          Lib.Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;

            text: model.title;
            color: model.selected ? "#fff" : ma.containsMouse ? "#a0a0a0" : "#888";
          }

          Lib.Icon {
            icon: icons.fa_times;
            color: close_ma.containsMouse ? "#fff" : "#888";
            anchors.verticalCenter: parent.verticalCenter;

            MouseArea {
              id: close_ma;

              hoverEnabled: true;
              anchors.fill: parent;

              onClicked: {
                modelData.close();
              }
            }
          }
        }
      }
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#282C34";
  }
}
