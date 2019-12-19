import QtQuick 2.12
import QtQuick.Controls 2.12

import Lib 1.0 as Lib

Item {
  id: root;

  Editor {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    anchors.topMargin: 8;
  }
}
