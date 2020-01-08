import QtQuick 2.12

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Item  {
  property alias controls: infoView.controls;
  property var file: App.document.file;
  visible: !App.details.collapsed;

  Item {
    id: tabs;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    height: 30;

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;

      height: 1;
      color: "#181A1F"
    }

    Row {
      anchors.fill: parent;

      Lib.Button {
        anchors.verticalCenter: parent.verticalCenter;

        iconSize: 16;
        icon: icons.fa_info_circle;
        label.text: "Info"
        width: parent.width / 2;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.info;

        onClicked: App.details.showInfo();
      }

      Lib.Button {
        anchors.verticalCenter: parent.verticalCenter;

        iconSize: 16;
        icon: icons.fa_cube;
        label.text: "Type List"
        width: parent.width / 2;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.types;

        onClicked: App.details.showTypes();
      }
    }
  }


  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: tabs.bottom;
    anchors.bottom: parent.bottom;

    anchors.leftMargin: 8;
    anchors.rightMargin: 8;
    anchors.bottomMargin: 8;

    Info {
      id: infoView;

      anchors.fill: parent;
      visible: App.details.info;
      enabled: visible;
    }

    TypeInfo.List {
      anchors.fill: parent;
      visible: App.details.types;
      enabled: visible;
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.top: tabs.bottom;
    anchors.bottom: parent.bottom;

    width: 1;
    color: "#181A1F"
  }
}
