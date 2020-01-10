import QtQuick 2.12

import UI 1.0 as UI

UI.List {
  title: "Enum Values"
  visible: model != undefined;

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
      id: _name;

      anchors.left: _ic.right;
      anchors.right: _value.left;
      anchors.verticalCenter: parent.verticalCenter;

      topPadding: 4;
      bottomPadding: 4;

      font.pointSize: 13;
      text: modelData.name;
      color: "#fff";
    }

    UI.Label {
      id: _value;

      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;

      text: modelData.value;
    }
  }
}
