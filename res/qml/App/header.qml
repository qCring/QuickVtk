import QtQuick 2.6

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Rectangle {
  id: root;

  height: 35
  property var file: Controllers.document.file;
  property bool modified: file != undefined && file.modified;

  color: "#21252B"

  Menu {
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.left: parent.left;
    anchors.leftMargin: 8;
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

      onClicked: Controllers.document.run();
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#282C34";
  }
}
