import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  height: 30;

  Row {
    id: arrows;

    anchors.left: parent.left;
    anchors.leftMargin: 8;
    anchors.verticalCenter: parent.verticalCenter;
    anchors.verticalCenterOffset: 2;
    spacing: 8;

    Lib.Icon {
      icon: icons.fa_chevron_left;
      anchors.verticalCenter: parent.verticalCenter;
      font.pointSize: 12;
      color: ma_prev.containsMouse ? "#fff" : "#9DA5B4"

      MouseArea {
        id: ma_prev;
        anchors.fill: parent
        anchors.margins: -2;
        onClicked: App.document.selectPrevious();
        hoverEnabled: true;
      }
    }

    Lib.Icon {
      icon: icons.fa_chevron_right;
      anchors.verticalCenter: parent.verticalCenter;
      font.pointSize: 12;
      color: ma_next.containsMouse ? "#fff" : "#9DA5B4"

      MouseArea {
        id: ma_next;
        anchors.fill: parent;
        anchors.margins: -2;
        onClicked: App.document.selectNext();
        hoverEnabled: true;
      }
    }
  }

  Row {
    anchors.left: arrows.right;
    anchors.bottom: parent.bottom;
    anchors.right: parent.right;
    anchors.leftMargin: 8;

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
            color: model.selected || ma.containsMouse ? "#fff" : "#9DA5B4";
          }

          Lib.Icon {
            icon: icons.fa_times;
            color: close_ma.containsMouse ? "#fff" : "#9DA5B4";
            anchors.verticalCenter: parent.verticalCenter;
            font.pointSize: 10;

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
