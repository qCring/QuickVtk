import QtQuick 2.6
import Lib 1.0 as Lib

Rectangle {

  property alias message: label.text;

  Row {
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
