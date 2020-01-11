import QtQuick 2.12

import UI 1.0 as UI

Item {
  anchors.fill: parent;
  anchors.topMargin: 8;

  Item { // search + listview
    anchors.fill: parent;

    visible: !detail.symbol;

    Search {
      id: _search;

      anchors.left: parent.left;
      anchors.right: parent.right;

    }

    UI.Area {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;
      anchors.top: _search.bottom;

      UI.ListView {
        clip: true;

        model: App.typeList;
        anchors.fill: parent;

        delegate: Item {
          anchors.left: parent.left;
          anchors.right: parent.right;
          height: _label.height;

          UI.Icon {
            id: _ic;

            anchors.left: parent.left;
            anchors.leftMargin: 8;
            anchors.verticalCenter: parent.verticalCenter;

            icon: icons.fa_cube;
            color: "#872BCB";
          }

          UI.Label {
            id: _label;

            anchors.left: _ic.right;
            anchors.right: _type.left;
            anchors.verticalCenter: parent.verticalCenter

            leftPadding: 8;
            topPadding: 4;
            bottomPadding: 4;

            text: modelData.prefix + "." + modelData.name;
            color: "#fff";
          }

          UI.Label {
            id: _type;

            anchors.right: parent.right;
            anchors.rightMargin: 4;
            anchors.verticalCenter: parent.verticalCenter;
            text: modelData.type == 0 ? "A" : modelData.type == 1 ? "C" : "E";
            font.pointSize: 9;
            font.bold: true;
          }

          MouseArea {
            id: _ma;

            anchors.fill: parent;
            onClicked: detail.symbol = modelData;
          }
        }
      }
    }
  }

  Detail {
    id: detail;
  }
}
