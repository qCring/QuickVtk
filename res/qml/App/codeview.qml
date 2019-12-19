import QtQuick 2.12
import QtQuick.Controls 2.12

import Lib 1.0 as Lib

Item {
  id: root;

  Rectangle {
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    height: 30;
    color: "#282C34"
  }

  Editor {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: header.bottom;
    anchors.bottom: parent.bottom;
  }
}
