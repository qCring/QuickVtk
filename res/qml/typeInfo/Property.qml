import QtQuick 2.6

import "./../lib" as Lib

Item {
    id: root;

    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: 22;

    property color typeColor: "#9DA5B4"

    Row {
        id: labels;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: rwRow.left;
        anchors.bottom: parent.bottom;
        anchors.leftMargin: 24;

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            font.pixelSize: 12;
            color: "#fff";

            text: item.name + ":  ";
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            visible: item.sequence;
            font.pixelSize: 12;
            color: root.typeColor;
            text: "list <"
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            font.pixelSize: 12;
            color: item.sequence ? "#fff" : root.typeColor;

            text: item.type;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            visible: item.sequence;
            font.pixelSize: 12;
            color: root.typeColor;
            text: ">"
        }
    }

    Row {
        id: rwRow;

        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: 4;

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            visible: item.readable;
            text: "R";
            font.pixelSize: 8;
            font.bold: true;
            color: "#6E7582";
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            visible: item.writable;
            text: "W";
            font.pixelSize: 8;
            font.bold: true;
            color: "#6E7582";
        }
    }
}
