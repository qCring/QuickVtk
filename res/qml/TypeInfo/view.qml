import QtQuick 2.12

import UI 1.0 as UI

Item {
  anchors.fill: parent;

  Item { // search + listview
    anchors.fill: parent;

    visible: !detail.symbol;

    Search {
      id: _search;

      anchors.left: parent.left;
      anchors.right: parent.right;
    }

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: _search.bottom;

      height: 1;
      color: "#181A1F";
      visible: _lv.scrolled;
    }

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: _footer.top;
      anchors.top: _search.bottom;

      UI.ListView {
        id: _lv;

        clip: true;

        model: App.typeList;

        anchors.fill: parent;
        anchors.leftMargin: 8;

        delegate: Item {
          anchors.left: parent.left;
          anchors.right: parent.right;
          height: _label.height;

          UI.Icon {
            id: _ic;

            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;

            rightPadding: 8;
            icon: icons.fa_cube;
            color: "#872BCB";
          }

          UI.Label {
            id: _label;

            anchors.left: _ic.right;
            anchors.right: _type.left;
            anchors.verticalCenter: parent.verticalCenter

            topPadding: 4;
            bottomPadding: 4;

            text: modelData.prefix + "." + modelData.name;
            color: "#fff";
          }

          UI.Label {
            id: _type;

            anchors.right: parent.right;

            anchors.verticalCenter: parent.verticalCenter;

            leftPadding: 8;
            rightPadding: 8;

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

    Item {
      id: _footer;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;

      height: 30;

      Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 1;
        color: "#181A1F";
      }

      UI.Badge {
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.rightMargin: 8;

        label.text: App.typeList.count + " / " + App.typeList.totalCount;
      }
    }
  }

  Detail {
    id: detail;
  }
}
