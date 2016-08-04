import QtQuick 2.6

import Utils 1.0 as Utils

Rectangle {
    id: root;

    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    anchors.margins: 8;

    width: 300;
    height: column.height;

    color: "#111";
    border.color: "#666";

    default property alias content: column.children;
    property alias title: label.text;

    MouseArea {
        anchors.fill: parent;
        propagateComposedEvents: false;
    }

    Column {
        id: column;

        anchors.left: parent.left;
        anchors.right: parent.right;

        anchors.leftMargin: 8;
        anchors.rightMargin: 8;

        topPadding: 4;
        bottomPadding: 4;

        spacing: 2;

        Utils.Label {
            id: label;

            text: "Properties"
            color: "#fff"
            font.bold: true;
        }
    }
}
