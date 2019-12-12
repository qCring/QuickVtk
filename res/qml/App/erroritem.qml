import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle {

  property alias message: label.text;
  height: content.height;

  Row {
    id: content;

    Lib.Icon {
      icon: icons.fa_times;
      anchors.verticalCenter: parent.verticalCenter;
    }

    Lib.Label {
      id: label;

      anchors.verticalCenter: parent.verticalCenter;
    }
  }
}
