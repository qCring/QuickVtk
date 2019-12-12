import QtQuick 2.12

import Lib 1.0 as Lib

Row {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height + 2;

    property var item;
    property color typeColor: "#9DA5B4"

    Lib.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 12;
        color: "#fff";

        text: item.name + ": ";
    }

    Lib.TagLabel {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.paramTypes;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#3D424B"
        color: "#00000000"
    }

    Lib.Icon {
        anchors.verticalCenter: parent.verticalCenter;

        icon: icons.fa_long_arrow_right;
        color: "#fff"
    }

    Lib.TagLabel {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.returnType;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#3D424B"
        color: "#00000000"
    }
}
