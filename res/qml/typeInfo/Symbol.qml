import QtQuick 2.6

import "./../lib" as Lib

Column {
    property var symbol;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    Item {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 24;

        Lib.TagLabel {
            id: typeTag;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;

            label.text: symbol.type[0];
            color: "#00000000"
            border.color: symbol.color;
            width: height;
            label.color: symbol.color;
            label.font.weight: Font.Bold;
            label.font.pixelSize: 10;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: typeTag.right;
            anchors.leftMargin:4;
            anchors.right: prefixLabel.left;

            text: symbol.name;
            color: symbol.color;
            font.bold: true;
            font.pixelSize: 12;
        }

        Lib.Label {
            id: prefixLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            text: symbol.prefix;
            color: "#6E7582"
            font.weight: Font.Bold;
            font.pixelSize: 10;
        }
    }

    Repeater {
        model: symbol.enumerations;
        delegate: Enumeration {
            item: model;
        }
    }

    Repeater {
        model: symbol.properties;
        delegate: Property {
            item: model;
        }
    }
}
