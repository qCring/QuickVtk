import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle {

  color: "#181A1F"

  Item {
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    height: label_time.height + 8;

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;

      height: 1;
      color: "#21252B"
    }

    Lib.Label {
      id: label_type;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.left: parent.left;
      leftPadding: 4;
      rightPadding: 4;

      text: "Type"
    }

    Lib.Label {
      anchors.verticalCenter: parent.verticalCenter;
      anchors.left: label_type.right;
      anchors.right: label_time.left;

      text: "Message"
    }

    Lib.Icon {
      id: label_time;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.right: parent.right;
      rightPadding: 4;

      icon: icons.fa_clock_o;
    }
  }

  Lib.List {
    anchors.top: header.bottom;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    model: App.console.items;

    delegate: Rectangle {

      anchors.left: parent.left;
      anchors.right: parent.right;
      height: label.height + 4;

      color: index % 2 ? "#1a1c22" : "#181A1F";

      Lib.Icon {
        id: ic;
        icon: modelData.type == 0 ? icons.fa_info_circle : modelData.type > 1 ? icons.fa_exclamation_triangle : "";
        color: modelData.type == 2 ? "#ffff00" : modelData.type == 3 ? "#ff0000" : "#777";
        width: label_type.width;
        font.pointSize: 9;
        anchors.verticalCenter: parent.verticalCenter;
        horizontalAlignment: Text.AlignHCenter
      }

      Lib.Label {
        id: label;
        text: modelData.message;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: ic.right;
        anchors.right: time.left;
      }

      Lib.Label {
        id: time;
        text: modelData.time;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        rightPadding: 4;
      }
    }
  }
}
