import QtQuick 2.12

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Item {
  id: root;

  height: 35
  property var file: App.document.file;
  property bool modified: file != undefined && file.modified;

  Menu {
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.left: parent.left;
    anchors.leftMargin: 4;
  }

  /*

  Row {
    anchors.top: parent.top;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.rightMargin: 8;

    Lib.Button {
      icon: icons.fa_play;
      label.text: root.modified ? "Run" : "-";
      anchors.verticalCenter: parent.verticalCenter;

      onClicked: App.document.run();
    }
  }*/

  Row {
    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.rightMargin: 8;
    spacing: 8;

    Rectangle {
      anchors.verticalCenter: parent.verticalCenter;

      border.color: App.console.collapsed ? "#6E7582" : "#2B68A4";
      color: "transparent"
      radius: 1;
      height: parent.height * 0.5;
      width: height * 1.4;

      Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.margins: 2;

        height: 3;
        color: App.console.collapsed ? "#6E7582" : "#2B68A4";
      }

      MouseArea {
          anchors.fill: parent
          onClicked: App.console.toggle();
      }
    }

    Rectangle {
      anchors.verticalCenter: parent.verticalCenter;

      border.color: App.details.collapsed ? "#6E7582" : "#2B68A4";
      radius: 1;
      color: "transparent"
      height: parent.height * 0.5;
      width: height * 1.4;

      Rectangle {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 2;

        width: 3;
        color: App.details.collapsed ? "#6E7582" : "#2B68A4";
      }

      MouseArea {
          anchors.fill: parent
          onClicked: App.details.toggle();
      }
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#333842";
  }
}
