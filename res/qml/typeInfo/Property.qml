import QtQuick 2.6

import "./../lib" as Lib

Item {
    id: root;

    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: 22;

    property color typeColor: "#9DA5B4"

    Lib.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: 24;

        font.pixelSize: 12;
        color: "#fff";

        text: item.name + ":  ";
    }

    Lib.Label {
        id: typePrefix;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: nameLabel.right;

        visible: item.sequence;
        font.pixelSize: 12;
        color: root.typeColor;
        text: "list <"
    }

    Lib.Label {
        id: typeLabel;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: typePrefix.visible ? typePrefix.right : nameLabel.right;

        font.pixelSize: 12;
        color: item.sequence ? "#fff" : root.typeColor;

        text: item.type;
    }

    Lib.Label {
        id: typeSuffix;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: typeLabel.right;
        anchors.right: rwLabel.left;
        anchors.rightMargin: 4;

        visible: item.sequence;
        font.pixelSize: 12;
        color: root.typeColor;
        text: ">"
    }

    Lib.Label {
        id: rwLabel;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        text: item.writable ? item.readable ? "R+W" : "W" : "R";
        font.pixelSize: 8;
        font.bold: true;
        color: "#9DA5B4";
    }
}
