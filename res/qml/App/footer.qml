import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle {
    height: 30
    color: "#21252B"

    Row {
      anchors.right: parent.right;
      anchors.rightMargin: 8;
      anchors.verticalCenter: parent.verticalCenter;
      spacing: 4;

      Lib.Icon {
        anchors.verticalCenter: parent.verticalCenter;
        icon: icons.fa_bug;
        visible: App.debugBuild;
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: "v. " + App.version;
      }
    }
}
