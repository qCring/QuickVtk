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
        icon: icons.fa_list_alt;
        width: parent.width / 3;
        frameless: true;
        use_toggle: true;
        toggle_on_click: false;
        toggle: App.details.info;

        onClicked: App.details.showInfo();
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

      Item {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        width: parent.width / 3;

        Lib.Icon {
          anchors.centerIn: parent;
          iconSize: 16;
          icon: icons.fa_bell;

          Lib.Label {
            id: _nlabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.right;
            anchors.leftMargin: 4;

            font.pointSize: 10;
            font.bold: true;
            text: App.notification.items.length;
            enabled: App.notification.items.length > 0;
          }
        }

        MouseArea {
          anchors.fill: parent;
          onClicked: App.details.showNotifications();
        }
      }
    }
  }

  Item {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: tabs.bottom;
    anchors.bottom: footer.top;
    //color: "#282C34"

    Item {
      id: _header;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;
      height: 50;

      Lib.Label {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;

        text: App.details.title;
        font.pointSize: 15;
        font.bold: true;
        color: "#fff";
      }
    }

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: _header.bottom;
      anchors.bottom: parent.bottom;

      anchors.leftMargin: 8;
      anchors.rightMargin: 8;
      anchors.topMargin: 8;
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

      Notifications {
        anchors.fill: parent;
        visible: App.details.notifications;
        enabled: visible;
      }
    }
  }

  Rectangle {
    anchors.left: parent.left;
    anchors.top: tabs.bottom;
    anchors.bottom: footer.top;

    width: 1;
    color: "#181A1F"
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
      color: "#181A1F"
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
