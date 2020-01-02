import QtQuick 2.12
import QtQuick.Controls 2.12

import Utils 1.0 as Utils

Item {
    id: root;

    property var from;
    property string bind;

    property alias label: nameLabel.text;
    property alias value: slider.value;
    property alias step: slider.stepSize;
    property alias min: slider.from;
    property alias max: slider.to;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height;

    Utils.Label {
        id: nameLabel;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 100;

        text: root.bind;
    }

    Utils.Label {
        id: valueLabel;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        width: 35;

        text: slider.value;
    }

    Slider {
        id: slider;

        anchors.left: nameLabel.right;
        anchors.right: valueLabel.left;
        anchors.verticalCenter: parent.verticalCenter;

        anchors.margins: 8;

        onValueChanged: {
          if (root.from) {
              root.from[root.bind] = value;
          }
        }

        handle: Rectangle {
          id: handle;
          width: 8;
          height: 8;
          radius: 4;
          x: slider.visualPosition * (slider.availableWidth - width / 2) + width / 2;
          anchors.verticalCenter: parent.verticalCenter;

          color: "#21252B"
        }

        background: Rectangle {
          implicitWidth: 200
          implicitHeight: 8
          color: "#21252B"
          border.color: "#1B1D23"
          radius: 2;

          Rectangle {
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.margins: 1;
            width: handle.x + handle.width * 1.5 - 2;

            radius: 2;
            color: "#2B68A4"
          }
       }
    }
}
