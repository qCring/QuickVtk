import QtQuick 2.12

import Lib 1.0 as Lib

Item  {

  property alias utilsView: utilsView;
  property var file: App.document.file;

  Item {
    id: utilsView;

    anchors.fill: parent;
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.bottom: parent.bottom;
    anchors.top: parent.top;

    width: 1;
    color: "#333842";
  }
}
