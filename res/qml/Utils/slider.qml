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
            width: 8;
            height: 8;
            radius: 4;

            color: "#2B68A4"
            border.color: "#fff"
        }

        /*style: SliderStyle {
            handle: Rectangle {
                width: 8;
                height: 8;
                radius: 4;

                color: "#2B68A4"
                border.color: "#fff"
            }

            groove: Rectangle {
                implicitWidth: 200
                implicitHeight: 8
                color: "#21252B"
                border.color: "#666"
                radius: 8

                Rectangle {
                    anchors.bottom: parent.bottom;
                    anchors.left: parent.left;
                    anchors.top: parent.top;

                    width: (control.value - control.minimumValue) / (control.maximumValue - control.minimumValue) * parent.width
                    radius: 8;
                    color: "#2B68A4"
                }
           }
        }
        */
    }
}
