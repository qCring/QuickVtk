import QtQuick 2.12

import Lib 1.0 as Lib

Item  {

  property alias utilsView: utilsView;
  property var file: App.document.file;

  Item {
    id: header;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    height: title.height + 4;

    Lib.Label {
      id: title;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.margins: 4;

      text: file ? file.title : "No File Selected"
      font.pointSize: 15;
    }
  }

  Item {
    id: utilsView;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.top: header.bottom;
  }
}
