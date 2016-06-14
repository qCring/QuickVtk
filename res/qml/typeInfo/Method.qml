import QtQuick 2.6

import "./../lib" as Lib

Column {
    id: root;

    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;

    property color typeColor: "#9DA5B4"

    Lib.Label {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 24;
        anchors.rightMargin: 4;

        font.pointSize: 12;
        color: "#fff";

        text: item.name;
    }

    Lib.Label {
        anchors.left: parent.left;
        anchors.leftMargin: 24;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        text: item.paramTypes + " -> " + item.returnType;
        font.pointSize: 9;
        color: "#9DA5B4";
    }
}
