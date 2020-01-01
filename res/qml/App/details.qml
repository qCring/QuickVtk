import QtQuick 2.12

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Item  {

  property alias utilsView: utilsView;
  property var file: App.document.file;
  visible: !App.details.collapsed;

  Item {
    id: tabs;
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    height: 30;

    Row {
      anchors.fill: parent;

      Lib.Button {
        anchors.verticalCenter: parent.verticalCenter;

        iconSize: 16;
        icon: icons.fa_list_alt;
        width: parent.width / 3;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.properties;

        onClicked: App.details.showProperties();
      }

      Lib.Button {
        anchors.verticalCenter: parent.verticalCenter;

        iconSize: 16;
        icon: icons.fa_question_circle;
        width: parent.width / 3;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.types;

        onClicked: App.details.showTypes();
      }

      Lib.Button {
        anchors.verticalCenter: parent.verticalCenter;

        iconSize: 16;
        icon: icons.fa_cog;
        width: parent.width / 3;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.settings;

        onClicked: App.details.showSettings();
      }
    }
  }

  Item {
    id: header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: tabs.bottom;
    height: title.height + 18;

    Lib.Label {
      id: title;
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.verticalCenter: parent.verticalCenter;
      anchors.leftMargin: 8;
      anchors.rightMargin: 8;

      text: App.details.title;
      font.pointSize: 14;
      font.bold: true;
    }

    Rectangle {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;

      height: 1;
      color: "#333842"
    }
  }

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: header.bottom;
    anchors.bottom: footer.top;

    Item {
      id: utilsView;

      anchors.fill: parent;
      visible: App.details.properties;
      enabled: visible;
    }

    TypeInfo.List {
      anchors.fill: parent;
      visible: App.details.types;
      enabled: visible;
    }

    Item {
      anchors.fill: parent;
      visible: App.details.settings;
      enabled: visible;
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
      color: "#333842"
    }

    Row {
      anchors.top: parent.top;
      anchors.bottom: parent.bottom;
      anchors.right: parent.right;
      anchors.rightMargin: 8;
      spacing: 8;

      Lib.Icon {
        anchors.verticalCenter: parent.verticalCenter;
        icon: icons.fa_bug;
        visible: App.debugBuild;
      }

      Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;
        text: "v. " + App.version;
      }
    }
  }
}
