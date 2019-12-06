import QtQuick 2.6
import QtQuick.Controls 1.4

import App 1.0 as App
import Lib 1.0 as Lib

Item {
    id: root;
    property var file: Controllers.document.file;

    Item {
      id: header;

      anchors.top: parent.top;
      anchors.left: parent.left;
      anchors.right: parent.right;
      height: content.height;

      Column {
        id: content;

        spacing: 4;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;

        Row {
          anchors.left: parent.left;
          anchors.right: parent.right;
          anchors.margins: 8;
          spacing: 8;

          Lib.Icon {
            icon: icons.fa_file;
          }

          Lib.Label {
            text: root.file != undefined ? root.file.path : "";
          }
        }

        Row {
          anchors.left: parent.left;
          anchors.right: parent.right;
          anchors.margins: 8;
          spacing: 8;

          Lib.Icon {
            icon: icons.fa_file;
          }

          Lib.Label {
            text: "last compiled"
          }
        }
      }
    }

    Editor {
      anchors.top: header.bottom;
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;
    }
}
