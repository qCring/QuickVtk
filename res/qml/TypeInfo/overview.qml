import QtQuick 2.12

import UI 1.0 as UI

Item {
  id: _root;

  anchors.fill: parent;

  signal selectSymbol(var symbol);

  Item {
    id: _header;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: _content.height;

    Column {
      id: _content;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: 8;
      anchors.rightMargin: 8;

      topPadding: 8;
      bottomPadding: 8;
      spacing: 8;

      Item {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: _title.height;

        UI.Label {
          id: _title;

          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter;

          font.pointSize: 15;
          color: "#fff";
          text: "Search";
        }

        UI.Label {
          anchors.right: parent.right;
          anchors.verticalCenter: parent.verticalCenter;
          anchors.rightMargin: 10;

          text: App.typeList.count + " / " + App.typeList.totalCount;
        }
      }

      Item {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: input.height;

        UI.TextInput {
          id: input;

          anchors.left: _ic.right;
          anchors.right: parent.right;
          anchors.top: parent.top;

          bottomPadding: 8;
          topPadding: 8;

          from: App.typeList;
          bind: "filter";

          immediate: true;

          onActiveFocusChanged: {
            App.typeList.visible = activeFocus;
          }
        }

        UI.Icon {
          id: _ic;

          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter;

          icon: icons.fa_search;
          color: input.activeFocus ? "#fff" : "#6E7582"
          rightPadding: 8;
        }

        UI.Button {
          id: _clear;

          anchors.right: parent.right;
          anchors.verticalCenter: parent.verticalCenter;

          frameless: true;
          icon: icons.fa_times_circle;
          visible: input.text.length > 0;

          onClicked: input.text = "";
        }
      }
    }
  }

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.top: _header.bottom;

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
          onClicked: _root.selectSymbol(modelData);
        }
      }
    }
  }
}
