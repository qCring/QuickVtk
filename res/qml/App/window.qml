import QtQuick 2.6
import QtQuick.Window 2.2

import Lib 1.0 as Lib
import Code 1.0 as Code
import TypeInfo 1.0 as TypeInfo

Window {
    id: root;

    color: "#282C34"

    FocusScope {
      id: defaultFocus;
    }

    MouseArea {
      anchors.fill: parent;

      onClicked: {
        console.log("root-click");
        defaultFocus.forceActiveFocus();
      }
    }

    Header {
      id: header

      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
    }

    Footer {
      id: footer

      anchors.left: parent.left
      anchors.right: parent.right
      anchors.bottom: parent.bottom
    }
}
