import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle  {
  id: root;

  color: "#282C34";
  visible: App.settings.visible;

  Rectangle {
    id: header;

    anchors.left: parent.left;
    anchors.top: parent.top;
    anchors.right: parent.right;

    height: 30;
    color: "#1a1c22"
  }

  Item {
    id: content;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: header.bottom;
    anchors.bottom: footer.top;

    Column {
      anchors.fill: parent;

      Lib.Button {
        label.text: "Clear Recent File History"
        onClicked: App.settings.reset();
      }
    }
  }

  Rectangle {
    id: footer;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;

    height: 30;
    color: "#1a1c22"

    Row {
      anchors.right: parent.right;
      anchors.rightMargin: 8;
      anchors.verticalCenter: parent.verticalCenter;
      spacing: 8;

      Lib.Button {
        icon: icons.fa_times;
        label.text: "Close"
        onClicked: App.settings.visible = false;
      }

      Lib.Button {
        icon: icons.fa_check;
        label.text: "OK"
        onClicked: App.settings.visible = false;
      }
    }
  }
}
