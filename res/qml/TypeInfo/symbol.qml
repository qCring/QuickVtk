import QtQuick 2.12

import UI 1.0 as UI

Column {
  id: col;

  property var symbol;

  anchors.left: parent.left;
  anchors.right: parent.right;

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height + 4;

    Rectangle {
      width: row.width;
      height: row.height;
      color: "#181A1F"
      radius: 4;
    }

    Row {
      id: row;

      anchors.left: parent.left;
      //anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;

        text: symbol.prefix + ".";
        color: "#6E7582"
        font.bold: true;
        font.pointSize: 12;
      }

      UI.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;

        text: symbol.name;
        color: "#fff"
        font.bold: true;
        font.pointSize: 12;
      }

      UI.Label {
        anchors.verticalCenter: parent.verticalCenter;

        visible: symbol.base != undefined && symbol.base;
        text: "  :  " + symbol.base;
        color: "#6E7582"
        font.bold: true;
        font.pointSize: 10;
      }
    }
  }

  Section {
    title: "values"
    model: symbol.enumerations;
    delegate: Enumeration {
        item: model;
        anchors.leftMargin: 12;
    }
  }

  Section {
    title: "properties"
    model: symbol.properties;
    delegate: Property {
        item: model;
        anchors.leftMargin: 12;
    }
  }

  Section {
    title: "methods"
    model: symbol.methods;
    delegate: Method {
        item: model;
        anchors.leftMargin: 12;
    }
  }
}
