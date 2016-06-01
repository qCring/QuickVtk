import QtQuick 2.5

import "./lib" as Lib

Item {
    property var symbol;

    anchors.left: parent.left;
    anchors.right: parent.right;

    height: 24;

    Row {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;

        spacing: 4;

        Lib.TagLabel {
            anchors.verticalCenter: parent.verticalCenter;
            label.text: symbol.type;
            color: symbol.color;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            text: symbol.prefix + "::" + symbol.name;
            font.pixelSize: 12;
        }
    }
}
