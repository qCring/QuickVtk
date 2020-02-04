import QtQuick 2.12

import UI 1.0 as UI

Item {
  id: root;

  anchors.fill: parent;

  property var symbol: null;

  Item {
    id: _header;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _content.height;

    Column {
      id: _content;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: 8;
      anchors.rightMargin: 8;

      topPadding: 8;
      bottomPadding: 8;
      spacing: 8;

      Item {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: _title.height;

        Row {
          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter;
          spacing: 8;

          UI.Icon {
            anchors.verticalCenter: parent.verticalCenter;
            icon: icons.fa_chevron_left;
            color: _ma.containsMouse ? "#fff" : "#9DA5B4";
          }

          UI.Label {
            id: _title;

            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 15;
            color: "#fff";
            text: symbol ? symbol.prefix + "." + symbol.name : "";
          }
        }

        MouseArea {
          id: _ma;

          anchors.fill: parent;

          hoverEnabled: true;
          onClicked: symbol = null;
        }
      }

      Column {
        anchors.left: parent.left;
        anchors.right: parent.right;

        topPadding: 8;
        bottomPadding: 8;
        spacing: 8;

        Row {
          anchors.left: parent.left;
          anchors.right: parent.right;
          spacing: 8;

          UI.Label {
            anchors.verticalCenter: parent.verticalCenter;
            width: _pref.width;
            text: "Name";
          }

          UI.Label {
            anchors.verticalCenter: parent.verticalCenter;
            text: symbol ? symbol.name : "";
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
      }
    }
  }

  Rectangle {
    id: _separator;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _header.bottom;

    height: 1;
    color: "#181A1F";
    visible: _sv.scrolled;
  }

  UI.ScrollView {
    id: _sv;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _header.bottom;
    anchors.bottom: parent.bottom;
    anchors.topMargin: 2;

    Column {
      anchors.left: parent.left;
      anchors.right: parent.right;

      bottomPadding: 64;
      spacing: 8;

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
}
