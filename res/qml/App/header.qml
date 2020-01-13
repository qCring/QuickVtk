import QtQuick 2.12

import UI 1.0 as UI
import TypeInfo 1.0 as TypeInfo

Rectangle {
  id: root;

  height: 35
  property var file: App.document.file;
  property bool modified: file != undefined && file.modified;
  color: "#282C34";

  Menu {
    id: _menu;

    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.left: parent.left;
    anchors.leftMargin: 4;
  }

  UI.Area {
    anchors.left: _menu.right;
    anchors.leftMargin: 16;
    anchors.verticalCenter: parent.verticalCenter;

    color: "#21252B";

    height: _label.height + 6;
    width: _row.width;

    Row {
      id: _row;

      anchors.left: parent.left;
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;

      rightPadding: 8;

      UI.Icon {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        enabled: file;

        leftPadding: 8;
        rightPadding: 8;

        icon: icons.fa_play;

        color: enabled ? _ma.containsMouse ? "#fff" : "#1D9FF2" : "#6E7582";

        MouseArea {
          id: _ma;

          anchors.fill: parent;

          hoverEnabled: true;
          onClicked: App.document.run();
        }
      }

      Rectangle {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        width: 1;
        color: "#181A1F";
      }

      UI.Label {
        id: _label;

        anchors.verticalCenter: parent.verticalCenter;

        leftPadding: 8;

        text: file ? file.title : "No File selected";
        color: file ? "#fff" : "#9DA5B4";
      }

      UI.Label {
        visible: file;

        anchors.verticalCenter: parent.verticalCenter;

        leftPadding: 8;
        rightPadding: 8;

        text: "|";
      }

      UI.Label {
        visible: file;

        anchors.verticalCenter: parent.verticalCenter;

        text: file ? " | " + file.timeStamp : "";
      }
    }
  }

  UI.Button {
    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.rightMargin: 8;

    icon: icons.fa_bars;
    frameless: true;
    onClicked: App.details.toggle();
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#181A1F";
  }
}
