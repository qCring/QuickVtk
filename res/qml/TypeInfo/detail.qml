import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  anchors.fill: parent;

  property var symbol: null;
  visible: symbol;

  Item {
    id: _header;

    anchors.top: parent.top;
    anchors.left: parent.left;
    anchors.right: parent.right;
    height: _label.height + 16;

    Lib.Button {
      id: _close;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      frameless: true;
      icon: icons.fa_chevron_left;
      onClicked: symbol = null;
    }

    Lib.Label {
      id: _label;

      anchors.left: _close.right;
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.leftMargin: 8;

      text: symbol ? symbol.prefix + "." + symbol.name : "";
      color: "#fff";
      font.bold: true;
      font.pointSize: 14;
    }
  }

  Item {
    id: _info;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _header.bottom;

    height: _infoCol.height;

    Column {
      id: _infoCol;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      Lib.Badge {
        label.text: symbol ? symbol.type == 0 ? "Abstract Class" : symbol.type == 1 ? "Class" : "Enum" : "" ;
        label.font.pointSize: 14;
      }

      Lib.Badge {
        label.text: symbol ? symbol.prefix : ""
      }
    }
  }

  Lib.Area {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _info.bottom;
    anchors.topMargin: 8;
    anchors.bottom: parent.bottom;

    Column {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      Properties {
        anchors.left: parent.left;
        anchors.right: parent.right;

        model: symbol ? symbol.properties : null;
      }

      Methods {
        anchors.left: parent.left;
        anchors.right: parent.right;

        model: symbol ? symbol.methods : null;
      }

      Enums {
        anchors.left: parent.left;
        anchors.right: parent.right;

        model: symbol ? symbol.enumerations : null;
      }
    }
  }
}
