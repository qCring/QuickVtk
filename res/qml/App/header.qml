import QtQuick 2.12

import UI 1.0 as UI
import TypeInfo 1.0 as TypeInfo

Rectangle {
  id: root;

  height: 35
  property var file: App.document.file;
  property bool modified: file != undefined && file.modified;
  color: "#282C34"

  Menu {
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.left: parent.left;
    anchors.leftMargin: 4;
  }

  UI.Button {
    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.rightMargin: 8;

    icon: icons.fa_bars;
    frameless: true;
    onClicked: App.details.toggle();
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: "#181A1F";
  }
}
