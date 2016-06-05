import QtQuick 2.6

import "./../lib" as Lib

Column {
    property var item;

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
                text: item.name;
                color: item.selected ? "#fff" : "#9DA5B4"
                font.pixelSize: 12;
            }
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            text: item.prefix;
            color: "#6E7582"

            font.weight: Font.Bold;
            font.pixelSize: 10;
        }


        MouseArea {
            anchors.fill: parent;
            onClicked: item.select();
        }
    }

    Repeater {
        model: item.selected ? item : 0;
        delegate: Group {
            group: model.group;
        }
    }
}
