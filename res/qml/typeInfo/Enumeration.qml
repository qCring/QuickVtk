import QtQuick 2.6

import "./../lib" as Lib

Row {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    property var item;

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
