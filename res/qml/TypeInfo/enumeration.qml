import QtQuick 2.12

import UI 1.0 as UI

Row {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    property var item;

    UI.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;
        font.pointSize: 12;
        color: "#fff";

        text: item.name + ":  ";
    }

    UI.Label {
        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 12;
        color: "#9DA5B4";
        text: item.value
    }
}
