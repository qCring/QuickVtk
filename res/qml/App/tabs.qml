import QtQuick 2.6
import Lib 1.0 as Lib

Rectangle {
  color: "#21252B"
  height: 30;

  Row {
    anchors.left: parent.left;
    anchors.bottom: parent.bottom;
    anchors.right: parent.right;

    Repeater {
      model: Controllers.document.files;

      Rectangle {
        anchors.bottom: parent.bottom;
        height: content.height + 10;
        width: content.width + 12;
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

          spacing: 4;
          anchors.top: parent.top;
          anchors.left: parent.left;
          anchors.topMargin: 4;
          anchors.leftMargin: 4;

          Lib.Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;

            text: model.title;
            color: model.selected ? "#2B68A4" : ma.containsMouse ? "#fff" : "#a0a0a0";
          }

          Lib.Icon {
            icon: icons.fa_times;
            color: close_ma.containsMouse ? "#fff" : "#a0a0a0";
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
