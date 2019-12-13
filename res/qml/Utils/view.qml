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

    Utils.Label {
      id: label;

      anchors.left: parent.left;
      anchors.right: parent.right;

      text: "Properties"
      color: "#fff"
      font.bold: true;
    }

    Column {
      id: contentColumn;

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
