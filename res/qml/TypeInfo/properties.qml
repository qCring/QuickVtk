import QtQuick 2.12

import Lib 1.0 as Lib

Group {
  title: "Properties"
  visible: model != undefined && model.length > 0;

  delegate: Item {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _name.height;

    Lib.Icon {
      id: _ic;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      rightPadding: 8;
      icon: icons.fa_cube;
    }

    Lib.Label {
      id: _name;

      anchors.left: _ic.right;
      anchors.verticalCenter: parent.verticalCenter;

      topPadding: 4;
      bottomPadding: 4;

      font.pointSize: 13;
      text: modelData.name;
      color: "#fff";
    }

    Lib.Label {
      visible: modelData.inherited;
      anchors.left: _name.right;
      anchors.verticalCenter: parent.verticalCenter;

      leftPadding: 8;

      text: "inherited";
    }

    Lib.Label {
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;

      text: modelData.type;
    }
  }
}
