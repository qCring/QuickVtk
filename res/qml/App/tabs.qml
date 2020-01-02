import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  height: 30;

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    height: 1;
    color: "#181A1F"
  }

  Row {
    id: arrows;

    anchors.left: parent.left;
    anchors.leftMargin: 8;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    spacing: 8;

    Lib.Icon {
      icon: icons.fa_chevron_left;
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;
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
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;
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
    anchors.top: parent.top;
    anchors.right: parent.right;
    anchors.leftMargin: 8;

    Repeater {
      model: App.document.files;

      Rectangle {
        anchors.bottom: parent.bottom;
        anchors.top: parent.top;
        width: content.width + 20;
        color: "#282C34"

        Rectangle {
          anchors.top: parent.top;
          anchors.right: parent.right;
          anchors.bottom: parent.bottom;

          width: 1;
          color: "#181A1F"
        }

        Rectangle {
          anchors.left: parent.left;
          anchors.right: parent.right;
          anchors.bottom: parent.bottom;

          height: 1;
          color: "#181A1F"
          visible: !model.selected;
        }

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
          anchors.horizontalCenter: parent.horizontalCenter;
          anchors.top: parent.top;
          anchors.bottom: parent.bottom;

          Lib.Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;

            text: model.title;
            color: model.selected || ma.containsMouse ? "#fff" : "#9DA5B4";
          }

          Lib.Icon {
            icon: icons.fa_times;
            color: close_ma.containsMouse ? "#fff" : "#9DA5B4";
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
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
}
