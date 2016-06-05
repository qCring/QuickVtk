import QtQuick 2.6

import "./../lib" as Lib

Item {
    property var item;

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
            label.text: item.type[0];
            color: "#00000000"
            border.color: item.color;
            width: height;
            label.color: item.color;
            label.font.weight: Font.Bold;
            label.font.pixelSize: 10;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            text: item.prefix + "::" + item.name;
            font.pixelSize: 12;
        }
    }
}
