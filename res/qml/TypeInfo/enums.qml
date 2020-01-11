import QtQuick 2.12

import UI 1.0 as UI

UI.List {
  title: "Enum Values"
  visible: model != undefined;

  delegate: Item {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _name.height;

    Tag {
      id: _ic;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      label.text: "E";
      label.color: "#C54632"
    }

    UI.Label {
      id: _name;

      anchors.left: _ic.right;
      anchors.right: _value.left;
      anchors.verticalCenter: parent.verticalCenter;

      topPadding: 4;
      bottomPadding: 4;
      leftPadding: 8;

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
