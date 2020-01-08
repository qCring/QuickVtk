import QtQuick 2.12

import Lib 1.0 as Lib

Item {
  anchors.fill: parent;

  Search {
    id: _search;

    anchors.left: parent.left;
    anchors.right: parent.right;
  }

  Lib.Area {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.top: _search.bottom;

    Lib.ListView {
      clip: true;

      model: App.typeList;
      anchors.fill: parent;

      delegate: Item {
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: _label.height;

        Lib.Icon {
          id: _ic;

          anchors.left: parent.left;
          anchors.leftMargin: 8;
          anchors.verticalCenter: parent.verticalCenter;

          icon: icons.fa_cube;
          iconSize: 11;
          color: "#872BCB"
        }

        Lib.Label {
          id: _label;

          anchors.left: _ic.right;
          anchors.verticalCenter: parent.verticalCenter

          leftPadding: 8;
          topPadding: 4;
          bottomPadding: 4;

          text: modelData.prefix + "." + modelData.name;
          color: "#fff";
        }

        Lib.Label {
          id: _type;

          anchors.right: parent.right;
          anchors.rightMargin: 4;
          anchors.verticalCenter: parent.verticalCenter;

          text: modelData.type;
          color: modelData.color;
          font.pointSize: 10;
        }

        MouseArea {
          id: _ma;

          anchors.fill: parent;
          hoverEnabled: true;
        }
      }
    }
  }
}
