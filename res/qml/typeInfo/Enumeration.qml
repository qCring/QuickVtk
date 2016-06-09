import QtQuick 2.6

import "./../lib" as Lib

Item {
    id: root;

    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height + 2;

    Row {
        id: labels;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        anchors.leftMargin: 24;

        Lib.Label {
            id: nameLabel;

            anchors.verticalCenter: parent.verticalCenter;
            font.pointSize: 12;
            color: "#fff";

            text: item.name + ":  ";
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            font.pointSize: 12;
            color: "#9DA5B4";
            text: item.value
        }
    }
}
