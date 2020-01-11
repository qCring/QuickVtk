import QtQuick 2.12

import UI 1.0 as UI

UI.List {
  title: "Properties"
  property var symbol;
  visible: _rep.model != undefined && _rep.model.length > 0;

  Repeater {
    id: _rep;

    model: symbol ? symbol.properties : null;

    delegate: Item {
      anchors.left: parent.left;
      anchors.right: parent.right;

      height: _name.height;

      Tag {
        id: _ic;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;

        label.text: "P";
        label.color: "#2B68A4";
      }

      UI.Label {
        id: _base;

        visible: modelData.inherited;

        anchors.left: _ic.right;
        anchors.verticalCenter: parent.verticalCenter;

        leftPadding: 8;
        text: "base";
      }

      UI.Label {
        id: _name;

        anchors.left: modelData.inherited ? _base.right : _ic.right;
        anchors.right: _type.left;
        anchors.verticalCenter: parent.verticalCenter;

        leftPadding: 8;

        font.pointSize: 13;
        text: modelData.name;
        color: "#fff";
      }

      TypeLabel {
        id: _type;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        text: modelData.type;
      }
    }
  }
}
