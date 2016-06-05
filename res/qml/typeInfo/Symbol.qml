import QtQuick 2.6

import "./../lib" as Lib

Column {
    property var symbol;

    anchors.left: parent.left;
    anchors.right: parent.right;

    Item {
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
                text: symbol.name;
                color: symbol.selected ? "#fff" : "#9DA5B4"
                font.pixelSize: 12;
            }
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            text: symbol.prefix;
            color: "#6E7582"

            font.weight: Font.Bold;
            font.pixelSize: 10;
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: symbol.select();
        }
    }

    Repeater {
        model: symbol.selected ? symbol.enumerations : 0;
        delegate: Enumeration {
            item: model;
        }
    }

    Repeater {
        model: symbol.selected ? symbol.properties : 0;
        delegate: Property {
            item: model;
        }
    }
}
