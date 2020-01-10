import QtQuick 2.12

import UI 1.0 as UI

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

        UI.Label {
            id: nameLabel;

            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 12;
            color: "#fff";

            text: item.name + ": ";
        }

        UI.Label {
            id: typeLabel;

            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 12;
            color: item.sequence ? "#fff" : root.typeColor;

            text: item.type;
        }
    }

    UI.Label {
        id: rwLabel;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        text: item.readonly ? "R" : "R+W";
        font.pointSize: 8;
        font.bold: true;
        color: "#6E7582";
    }
}
