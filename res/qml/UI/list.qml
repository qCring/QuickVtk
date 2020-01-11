import QtQuick 2.12

import UI 1.0 as UI

Column {
  anchors.left: parent.left;
  anchors.right: parent.right;
  spacing: 8;

  property alias title: _title.text;
  property alias model: _content.model;
  property alias delegate: _content.delegate;

  Item {
    id: _header;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _title.height;

    UI.Label {
      id: _title;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.rightMargin: 8;
      anchors.verticalCenter: parent.verticalCenter;

      topPadding: 8;

      font.pointSize: 14;
      color: "#fff";
    }
  }

  UI.Area {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _col.height;

    Column {
      id: _col;

      anchors.top: parent.top;
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: 8;
      anchors.rightMargin: 8;

      Repeater {
        id: _content;
      }
    }
  }
}
