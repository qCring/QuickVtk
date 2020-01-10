import QtQuick 2.12

import UI 1.0 as UI

UI.List {
  title: "Properties"
  visible: model != undefined && model.length > 0;

  delegate: Item {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _name.height;

    UI.Icon {
      id: _ic;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      rightPadding: 8;
      icon: icons.fa_cube;
    }

    UI.Label {
      id: _base;

      visible: modelData.inherited;

      anchors.left: _ic.right;
      anchors.verticalCenter: parent.verticalCenter;

      rightPadding: 8;
      text: "base";
    }

    UI.Label {
      id: _name;

      anchors.left: modelData.inherited ? _base.right : _ic.right;
      anchors.right: _type.left;
      anchors.verticalCenter: parent.verticalCenter;

      topPadding: 4;
      bottomPadding: 4;

      font.pointSize: 13;
      text: modelData.name;
      color: "#fff";
    }

    UI.Label {
      id: _type;

      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;

      text: modelData.type;
    }
  }
}
