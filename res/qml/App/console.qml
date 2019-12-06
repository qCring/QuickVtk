import QtQuick 2.6
import Lib 1.0 as Lib

Rectangle {

  color: "#181A1F"

  Rectangle {
    id: header;

    anchors.top: parent.top;
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: label.height + 8;
    color: "#21252B"

    Lib.Label {
      id: label;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.left: parent.left;
      anchors.leftMargin: 8;

      text: "Output"
    }

    Row {
      anchors.verticalCenter: parent.verticalCenter;
      anchors.right: parent.right;
      anchors.rightMargin: 8;

      Lib.Button {
        frameless: true;
        icon: icons.fa_trash;

        onClicked: {
          Controllers.console.clear();
        }
      }
    }
  }

  Lib.List {
    anchors.top: header.bottom;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    model: Controllers.console.items;
    delegate: Rectangle {

      anchors.left: parent.left;
      anchors.right: parent.right;
      height: label.height + 2;

      color: index % 2 ? "#1a1c22" : "#181A1F";

      Lib.Icon {
        id: ic;
        icon: modelData.type == 0 ? icons.fa_info_circle : modelData.type > 1 ? icons.fa_exclamation_triangle : "";
        width: 20;
        color: modelData.type == 2 ? "#ffff00" : modelData.type == 3 ? "#ff0000" : "#777";
        anchors.top: parent.top;
      }

      Lib.Label {
        id: label;
        text: modelData.message;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: ic.right;
        anchors.leftMargin: 8;
        anchors.right: time.left;
        anchors.rightMargin: 8;
      }

      Lib.Label {
        id: time;
        text: modelData.time;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.rightMargin: 8;
      }
    }
  }
}
