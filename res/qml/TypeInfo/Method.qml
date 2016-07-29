import QtQuick 2.6

import "./../Lib" as Lib

Row {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: nameLabel.height;

    property var item;
    property color typeColor: "#9DA5B4"

    Lib.Label {
        id: nameLabel;

        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 12;
        color: "#fff";

        text: item.name + ": ";
    }

    Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;

        text: "(";
        color: "#fff"
    }

    Lib.TagLabel {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.paramTypes;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#333842"
        color: "#00000000"
    }

    Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;

        text: ") ->";
        color: "#fff"
    }

    Lib.TagLabel {
        anchors.verticalCenter: parent.verticalCenter;

        label.text: item.returnType;
        label.font.pointSize: 9;
        label.color: "#9DA5B4";
        border.color: "#333842"
        color: "#00000000"
    }
}
