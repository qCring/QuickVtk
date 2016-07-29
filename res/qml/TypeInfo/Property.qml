import QtQuick 2.6

import "./../Lib" as Lib

Item {
    id: root;

    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height + 2;

    property color typeColor: "#9DA5B4"

    Row {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: nameLabel.height;

        Lib.Label {
            id: nameLabel;

            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 12;
            color: "#fff";

            text: item.name + ": ";
        }

        Lib.Label {
            id: typePrefix;

            anchors.verticalCenter: parent.verticalCenter;

            visible: item.sequence;
            font.pointSize: 12;
            color: root.typeColor;
            text: "list <"
        }

        Lib.Label {
            id: typeLabel;

            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 12;
            color: item.sequence ? "#fff" : root.typeColor;

            text: item.type;
        }

        Lib.Label {
            id: typeSuffix;

            anchors.verticalCenter: parent.verticalCenter;

            visible: item.sequence;
            font.pointSize: 12;
            color: root.typeColor;
            text: ">"
        }
    }

    Lib.Label {
        id: rwLabel;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        text: item.writable ? item.readable ? "R+W" : "W" : "R";
        font.pointSize: 8;
        font.bold: true;
        color: "#6E7582";
    }
}
