import QtQuick 2.12

import UI 1.0 as UI

Rectangle {
  property alias label: _label;
  width: height;
  height: _label.height + 4;
  radius: height / 2;
  color: "#21252B"

  UI.Label {
    id: _label;

    anchors.centerIn: parent;
    font.pointSize: 11;
  }
}
