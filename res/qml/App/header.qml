import QtQuick 2.12

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Item {
  id: root;

  height: 35
  property var file: App.document.file;
  property bool modified: file != undefined && file.modified;

  Menu {
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.left: parent.left;
    anchors.leftMargin: 4;
  }

  Row {
    anchors.top: parent.top;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.rightMargin: 8;

    Lib.Button {
      icon: icons.fa_play;
      label.text: root.modified ? "Run" : "-";
      anchors.verticalCenter: parent.verticalCenter;

      onClicked: App.document.run();
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#333842";
  }
}
