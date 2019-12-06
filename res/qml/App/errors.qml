import QtQuick 2.6

import Lib 1.0 as Lib

Item {
  id: root;

  property var file: Controllers.document.file;

  Lib.Label {
    id: title;

    anchors.left: parent.left;
    anchors.right: parent.right;
    text: "Errors";
  }

  Lib.List {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: title.bottom;
    anchors.bottom: parent.bottom;

    model: file != undefined ? file.errors : null;
    delegate: ErrorItem {
      message: model.line + ":" + model.column + " - " + model.message
    }
  }
}
