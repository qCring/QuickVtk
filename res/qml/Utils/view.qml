import QtQuick 2.12

import Utils 1.0 as Utils
import Lib 1.0 as Lib

Item {
  id: root;

  anchors.left: parent ? parent.left : undefined;
  anchors.right: parent ? parent.right : undefined;
  anchors.top: parent ? parent.top : undefined;
  anchors.margins: 8;

  property var file: null;
  property bool selected: false;
  property bool expanded: true;
  property alias title: label.text;
  default property alias content: contentColumn.children;

  height: column.height;

  Column {
    id: column;

    anchors.left: parent.left;
    anchors.right: parent.right;

    anchors.leftMargin: 8;
    anchors.rightMargin: 8;

    topPadding: 4;
    bottomPadding: 4;

    spacing: 2;

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;

      height: label.height;

      Lib.Icon {
        id: icon;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: parent.height;
        icon: root.expanded ? icons.fa_caret_down : icons.fa_caret_right;
        color: ma.containsMouse ? "#fff" : "#9DA5B4";
      }

      Utils.Label {
        id: label;

        anchors.left: icon.right;
        anchors.leftMargin: 8;

        text: "Properties"
        color: "#fff"
        font.bold: true;
      }

      MouseArea {
        id: ma;

        anchors.fill: parent;
        onClicked: root.expanded = !root.expanded;
        hoverEnabled: true;
      }
    }

    Column {
      id: contentColumn;

      visible: root.expanded;

      anchors.left: parent.left;
      anchors.right: parent.right;

      spacing: 8;
    }
  }

  onSelectedChanged: {
    if (selected) {
      root.visible = root.enabled = true;
      root.parent = utilsView;
    } else {
      root.visible = root.enabled = false;
      root.parent = null;
    }
  }

  onFileChanged: {
    if (file) {
      root.selected = Qt.binding (function() { return file.selected; });
    }
  }

  Component.onCompleted: {
    this.file = App.document.file;
    root.parent = utilsView;
  }
}
