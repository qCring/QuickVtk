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
      onClicked: defaultFocus.forceActiveFocus();
    }

    Preview {
      utilsView: context.utilsView;

      anchors.top: header.bottom;
      anchors.left: parent.left;
      anchors.right: hSplit.left;
      anchors.bottom: vSplit.top;
    }

    Rectangle {
      id: hSplit;

      x: parent.width - 400;
      width: 4;
      color: "#21252B"

      anchors.bottom: footer.top;
      anchors.top: header.bottom;

      MouseArea {
        anchors.fill: parent;
        drag.target: parent;
        drag.axis: Drag.XAxis;
      }
    }

    Rectangle {
      id: vSplit;

      y: parent.height - 300;
      height: vLabel.height + 8;
      color: "#282C34"

      anchors.left: parent.left;
      anchors.right: hSplit.left;

      Row {
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 8;
        spacing: 8;

        Lib.Button {
          id: vLabel;
          frameless: true
          anchors.verticalCenter: parent.verticalCenter;
          icon: icons.fa_terminal;
          label.text: "Console";
        }

        /*Lib.Label {
          id: vLabel;
          anchors.verticalCenter: parent.verticalCenter;
          text: "Console"
        }*/
      }

      MouseArea {
        anchors.fill: parent;
        drag.target: parent;
        drag.axis: Drag.YAxis;
        drag.minimumY: header.height;
        drag.maximumY: root.height - footer.height - parent.height;

        onReleased: {
          const py = vSplit.y + mouse.y;

          if (py < root.height / 2) {
            vSplit.anchors.top = root.top;
            vSplit.anchors.bottom = undefined;
          } else {
            vSplit.anchors.top = undefined;
            vSplit.anchors.bottom = root.bottom;
          }

          vSplit.y = vSplit.y;
        }
      }
    }

    Context {
      id: context;

      anchors.left: hSplit.right;
      anchors.right: parent.right;
      anchors.top: header.bottom;
      anchors.bottom: footer.top;
    }

    Console {
      anchors.top: vSplit.bottom;
      anchors.left: parent.left;
      anchors.right: context.left;
      anchors.bottom: footer.top;
    }

    Footer {
      id: footer

      anchors.left: parent.left
      anchors.right: parent.right
      anchors.bottom: parent.bottom
    }

    Header {
      id: header

      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
    }
}
