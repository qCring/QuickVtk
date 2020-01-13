import QtQuick 2.12

import UI 1.0 as UI

Item {
  id: root;

  anchors.fill: parent;

  property var symbol: null;
  visible: symbol;

  Item {
    id: _header;

    anchors.top: parent.top;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 8;
    anchors.topMargin: 8;

    height: _label.height + 16;

    UI.Button {
      id: _close;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      frameless: true;
      icon: icons.fa_chevron_left;
      onClicked: symbol = null;
    }

    UI.Label {
      id: _label;

      anchors.left: _close.right;
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.leftMargin: 8;

      text: symbol ? symbol.prefix + "." + symbol.name : "";
      color: "#fff";
      font.pointSize: 15;
    }
  }

  Column {
    id: _info;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _header.bottom;
    anchors.topMargin: 8;
    anchors.leftMargin: 16;

    bottomPadding: 8;
    spacing: 8;

    Row {
      anchors.left: parent.left;
      anchors.right: parent.right;
      spacing: 8;

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;
        width: _pref.width;
        text: "Type";
      }

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: symbol ? symbol.type == 0 ? "Abstract Class" : symbol.type == 1 ? "Class" : "Enum" : "";
        color: "#fff";
      }
    }

    Row {
      anchors.left: parent.left;
      anchors.right: parent.right;
      spacing: 8;

      visible: symbol && symbol.base != undefined;

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;
        width: _pref.width;
        text: "Base";
      }

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: symbol && symbol.base ? symbol.base : "";
        color: "#fff";
      }
    }

    Row {
      anchors.left: parent.left;
      anchors.right: parent.right;
      spacing: 8;

      UI.Label {
        id: _pref;

        anchors.verticalCenter: parent.verticalCenter;
        text: "Module";
      }

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: symbol ? symbol.prefix : "";
        color: "#fff";
      }
    }
  }

  Rectangle {
    id: _separator;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _info.bottom;

    height: 1;
    color: "#181A1F";
    visible: _sv.scrolled;
  }

  UI.ScrollView {
    id: _sv;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _separator.bottom;
    anchors.bottom: _footer.top;

    Column {
      anchors.left: parent.left;
      anchors.right: parent.right;
      bottomPadding: 64;

      Properties {
        anchors.left: parent.left;
        anchors.right: parent.right;

        symbol: root.symbol;
      }

      Methods {
        anchors.left: parent.left;
        anchors.right: parent.right;

        symbol: root.symbol;
      }

      Enums {
        anchors.left: parent.left;
        anchors.right: parent.right;

        symbol: root.symbol;
      }
    }
  }

  Item {
    id: _footer;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    height: 30;

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      height: 1;
      color: "#181A1F";
    }
  }
}
