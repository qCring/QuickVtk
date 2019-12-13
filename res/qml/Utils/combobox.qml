import QtQuick 2.12
import QtQuick.Controls 2.12

import Lib 1.0 as Lib

Item {
  id: root;

  anchors.left: parent.left;
  anchors.right: parent.right;
  height: _label.height + 8;

  property alias model: control.model;
  property alias label: label.text;
  property alias currentIndex: control.currentIndex;

  signal indexChanged(var index);

  Lib.Label {
    id: label;

    anchors.left: parent.left;
    anchors.verticalCenter: parent.verticalCenter;
    width: 100;

    text: root.bind;
  }

  ComboBox {
    id: control;

    anchors.left: label.right;
    anchors.right: parent.right;
    anchors.leftMargin: 8;
    anchors.verticalCenter: parent.verticalCenter;

    bottomInset: 0;
    onCurrentIndexChanged: root.indexChanged(currentIndex);

    indicator: Lib.Icon {
      id: _indicator;

      anchors.right: parent.right;
      anchors.rightMargin: 8;
      anchors.verticalCenter: _label.verticalCenter;

      icon: icons.fa_caret_down;
    }

    contentItem: Lib.Label {
      id: _label;

      anchors.left: parent.left;
      anchors.right: _indicator.left;
      anchors.leftMargin: 4;
      anchors.rightMargin: 4;

      text: control.displayText;
      elide: Text.ElideRight;
      verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
      id: _background;

      implicitWidth: 120
      color: "#21252B"
      border.color: "#666"
      border.width: control.visualFocus ? 2 : 1
      radius: 2
    }

    delegate: Lib.Label {
      //width: control.width
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.leftMargin: 4;
      anchors.rightMargin: 4;
      topPadding: 4;
      text: modelData
      color: control.highlightedIndex === index || del_ma.containsMouse ? "#fff" : "#9DA5B4";

      MouseArea {
        id: del_ma;
        anchors.fill: parent
        hoverEnabled: true;

        onClicked: {
          control.currentIndex = index;
          root.forceActiveFocus();
        }
      }
    }


    popup: Popup {
      y: control.height - 1
      width: control.width
      implicitHeight: contentItem.implicitHeight
      padding: 1

      contentItem: Column {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        Repeater {
          model: control.popup.visible ? control.delegateModel : null
          Lib.Label {
            text: modelData;
          }
        }
      }

      background: Rectangle {
        color: "#21252B"
        border.color: "#666"
        radius: 2
      }
    }
  }
}
