import QtQuick 2.12

import Lib 1.0 as Lib

Item  {

  property alias utilsView: utilsView;
  property var file: App.document.file;
  visible: App.showInspector;

  Item {
    id: header;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    height: 30;

    Lib.Label {
      id: title;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.margins: 4;

      text: file ? file.title : "No File Selected"
      font.pointSize: 15;
    }

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;

      height: 1;
      color: "#333842"
    }
  }

  Item {
    id: utilsView;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.top: header.bottom;
  }

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    height: 30;

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      height: 1;
      color: "#333842"
    }

    Row {
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;
      anchors.right: parent.right;
      anchors.rightMargin: 8;
      spacing: 8;

      Lib.Icon {
        anchors.verticalCenter: parent.verticalCenter;
        icon: icons.fa_bug;
        visible: App.debugBuild;
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: "v. " + App.version;
      }
    }
  }
}
