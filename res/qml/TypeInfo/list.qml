import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  anchors.fill: parent;

  Search {
    id: _search;

    anchors.left: parent.left;
    anchors.right: parent.right;
  }

  Lib.ListView {
      clip: true;

      model: App.typeList;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;
      anchors.top: _search.bottom;

      delegate: Item {
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: _label.height;

        Lib.Label {
          id: _label;

          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter

          leftPadding: 8;
          topPadding: 4;
          bottomPadding: 4;

          text: modelData.prefix + "." + modelData.name;
          color: _ma.containsMouse ? "#fff" : "#9DA5B4"
        }

        Lib.Badge {
          anchors.verticalCenter: parent.verticalCenter
          anchors.right: parent.right;
          anchors.rightMargin: 4;

          label.text: modelData.type;
          label.color: modelData.color;
        }

        MouseArea {
          id: _ma;

          anchors.fill: parent;
          hoverEnabled: true;
        }
      }
  }
}
