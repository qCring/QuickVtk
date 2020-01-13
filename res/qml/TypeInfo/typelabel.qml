import QtQuick 2.12

import UI 1.0 as UI

Rectangle {
  id: root;

  property string text: "";
  width: _row.width + 8;
  height: _label.height + 2;
  color: "#21252B";
  radius: 4;

  Row {
    id: _row;
    anchors.centerIn: parent;
    spacing: 2;

    UI.Label {
      anchors.verticalCenter: parent.verticalCenter;
      text: "{";
      color: "#fff"
      font.pointSize: 11;
    }

    UI.Label {
      id: _label;

      anchors.verticalCenter: parent.verticalCenter;
      text: root.text;
      font.pointSize: 11;
    }

    UI.Label {
      anchors.verticalCenter: parent.verticalCenter;
      text: "}";
      color: "#fff";
      font.pointSize: 11;
    }
  }
}
