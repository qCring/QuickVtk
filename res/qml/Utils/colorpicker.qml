import QtQuick 2.12
import QtQuick.Dialogs 1.2

import Lib 1.0 as Lib

Item {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    height: label.height;

    property alias label: label.text;
    property alias color: picker.color;

    property var from;
    property string bind;

    Lib.Label {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 100;

        text: root.bind;
    }

    Lib.Label {
        anchors.left: rect.right;
        anchors.leftMargin: 8;
        text: picker.color;
    }

    Rectangle {
        id: rect;

        anchors.left: label.right;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;

        width: 32;
        height: 14;
        radius: 2;

        border.color: "#666";
        color: picker.color;

        MouseArea {
            anchors.fill: parent;
            onClicked:  picker.open();
        }
    }

    ColorDialog {
        id: picker
        onAccepted: root.from[root.bind] = picker.color;
    }
}
