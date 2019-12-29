import QtQuick 2.12
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

    Item {
      id: hSplit;

      x: parent.width - 400;
      width: 4;

      anchors.bottom: footer.top;
      anchors.top: header.bottom;

      MouseArea {
        anchors.fill: parent;
        drag.target: parent;
        drag.axis: Drag.XAxis;
      }
    }

    Item {
      id: vSplit;

      height: vLabel.height + 4;

      anchors.left: parent.left;
      anchors.right: hSplit.left;
      anchors.bottom: footer.top;
      anchors.bottomMargin: App.console.collapsed ? 0 : 200;

      Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        height: 1;
        color: "#282C34"
      }

      MouseArea {
        anchors.fill: parent;

        onDoubleClicked: App.console.toggle();
      }

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
          onClicked: App.console.toggle();
        }

        Rectangle {
          color: "#181A1F"
          width: label_logs.width + 12;
          height: label_logs.height + 2;
          anchors.verticalCenter: parent.verticalCenter;
          radius: 4;

          Lib.Label {
            id: label_logs;
            anchors.centerIn: parent;
            text: App.console.items.length;
            font.pointSize: 10;
          }
        }
      }

      Row {
        anchors.right: parent.right;
        anchors.top: parent.top;

        Lib.Button {
          label.text: "Preview"
          use_toggle: true;
          toggle_on_click: false;
          toggle: !App.document.showSource;
          color: toggle ? "#181A1F" : "#31353B"
          radius: 0;

          onClicked: {
            App.document.showSource = false;
          }
        }

        Lib.Button {
          label.text: ".qml"
          use_toggle: true;
          toggle_on_click: false;
          toggle: App.document.showSource;
          color: toggle ? "#181A1F" : "#31353B"
          radius: 0;

          onClicked: {
            App.document.showSource = true;
          }
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
      anchors.right: hSplit.left;
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
