import QtQuick 2.12

import UI 1.0 as UI

Rectangle {

  color: "#21252B"
  visible: !App.console.collapsed;

  Rectangle {
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    height: label_type.height + 8;
    color: "#282C34"

    UI.Label {
      id: label_type;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.left: parent.left;

      leftPadding: 20;
      rightPadding: 20;

      text: "Type"
    }

    UI.Label {
      anchors.verticalCenter: parent.verticalCenter;
      anchors.left: label_type.right;
      anchors.right: label_time.left;

      text: "Description"
    }

    UI.Label {
      id: label_time;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.right: _stickyBtn.left;

      text: "Time"
    }

    UI.Icon {
      id: _stickyBtn;

      anchors.right: parent.right;
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;

      leftPadding: 6;
      rightPadding: 6;

      icon: icons.fa_long_arrow_down;
      color: _stickyMa.containsMouse ? "#fff" : _lv.sticky ? "#2B68A4" : "#9DA5B4";

      MouseArea {
        id: _stickyMa;

        anchors.fill: parent;

        hoverEnabled: true;
        onClicked: _lv.sticky = !_lv.sticky;
      }
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    height: 1;
    color: "#181A1F";
  }

  UI.ListView {
    id: _lv;

    anchors.top: header.bottom;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: footer.top;

    model: App.console.items;

    delegate: Item {

      anchors.left: parent.left;
      anchors.right: parent.right;
      height: _description.height + 4;

      Item {
        id: _label;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        width: label_type.width;

        UI.Label {
          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter;

          leftPadding: 4;
          rightPadding: 4;
          text: modelData.label;
          font.bold: modelData.type > 1;
          color: modelData.type == 2 ? "#D4B05E" : modelData.type == 3 ? "#C54632" : "#9DA5B4";
        }
      }

      UI.Label {
        id: _description;

        text: modelData.description;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: _label.right;
        anchors.right: _time.left;
      }

      UI.Label {
        id: _time;

        text: modelData.time;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        rightPadding: 4;
      }
    }
  }

  Item {
    id: footer;

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

    UI.Button {
      id: btn_clear;

      anchors.verticalCenter: parent.verticalCenter;
      anchors.right: parent.right;
      anchors.rightMargin: 8;

      frameless: true;
      icon: icons.fa_trash;
      label.text: "Clear";
      onClicked: App.console.clear();
    }
  }
}
