import QtQuick 2.12
import QtQuick.Dialogs 1.2

import UI 1.0 as UI

Item {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    height: label.height;

    property alias label: label.text;
    property alias color: picker.color;

    property var from;
    property string bind;

    UI.Label {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 100;

        text: root.bind;
    }

    UI.Label {
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

        border.color: "#1B1D23";
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

    Component.onCompleted: root.from[root.bind] = color;
}
