import QtQuick 2.12

import UI 1.0 as UI

Column {
  anchors.left: parent.left;
  anchors.right: parent.right;
  spacing: 8;

  property alias title: _title.text;
  property bool collapsible: true;
  property bool collapsed: false;
  default property alias content: _col.children;

  Item {
    id: _header;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _title.height + 8;

    UI.Button {
      anchors.verticalCenter: parent.verticalCenter;

      icon: collapsed ? icons.fa_caret_right : icons.fa_caret_down;
      visible: collapsible;
      frameless: true;
      onClicked: collapsed = !collapsed;
    }

    UI.Label {
      id: _title;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: collapsible ? 20 : 0;
      anchors.rightMargin: 8;
      anchors.verticalCenter: parent.verticalCenter;

      font.pointSize: 15;
      color: "#fff";
    }
  }

  UI.Area {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _col.height;

    visible: !collapsed;

    Column {
      id: _col;

      anchors.top: parent.top;
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: 8;
      anchors.rightMargin: 8;

      spacing: 8;
      topPadding: 8;
      bottomPadding: 8;
    }
  }
}
