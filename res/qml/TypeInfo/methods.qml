import QtQuick 2.12

import Lib 1.0 as Lib

Group {
  title: "Methods";
  visible: model != undefined && model.length > 0;

  delegate: Item {
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _label.height;

    Lib.Icon {
      id: _ic;

      anchors.left: parent.left;
      anchors.verticalCenter: parent.verticalCenter;

      rightPadding: 8;
      icon: icons.fa_cube;
    }

    Lib.Label {
      id: _base;

      visible: modelData.inherited;

      anchors.left: _ic.right;
      anchors.verticalCenter: parent.verticalCenter;

      rightPadding: 8;
      text: "base";
    }

    Row {
      anchors.left: modelData.inherited ? _base.right : _ic.right;
      anchors.verticalCenter: parent.verticalCenter;

      Lib.Label {
        id: _name;

        anchors.verticalCenter: parent.verticalCenter;

        topPadding: 4;
        bottomPadding: 4;

        font.pointSize: 13;
        text: modelData.name + " (";
        color: "#fff";
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 13;
        rightPadding: 2;
        leftPadding: 2;
        text: modelData.paramTypes;
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 13;
        color: "#fff"
        text: ")";
      }

      Lib.Icon {
        anchors.verticalCenter: parent.verticalCenter;
        rightPadding: 8;
        leftPadding: 8;

        icon: icons.fa_long_arrow_right;
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 13;
        text: modelData.returnType;
      }
    }
  }
}
