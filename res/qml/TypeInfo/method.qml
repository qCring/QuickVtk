import QtQuick 2.12

import UI 1.0 as UI

Row {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height + 2;

    property var item;
    property color typeColor: "#9DA5B4"

    UI.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 12;
        color: "#fff";

        text: item.name + ": ";
    }

    UI.Badge {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.paramTypes;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#3D424B"
        color: "#00000000"
    }

    UI.Icon {
        anchors.verticalCenter: parent.verticalCenter;

        icon: icons.fa_long_arrow_right;
        color: "#fff"
    }

    UI.Badge {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.returnType;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#3D424B"
        color: "#00000000"
    }
}
