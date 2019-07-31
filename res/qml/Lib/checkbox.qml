import QtQuick 2.6

import Lib 1.0 as Lib

Item {
    id: root;

    width: row.width + 4;
    height: label.height + 6;

    property var from;
    property string bind;
    property bool checked;

    property alias label: label;

    Row {
        id: row;

        anchors.centerIn: parent;
        spacing: 4;

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter;

            width: 14;
            height: 14;

            color: ma.pressed ? "#181A1F" : ma.containsMouse ? "#363C46" : "#333842"
            border.color: "#666";
            radius: 2;

            Lib.Icon {
                anchors.centerIn: parent;

                color: "#fff";
                visible: root.checked;
                icon: icons.fa_check;
            }
        }

        Lib.Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;
        }
    }

    MouseArea {
        id: ma;

        anchors.fill: parent;
        hoverEnabled: true;

        onClicked: {
            root.forceActiveFocus();

            if (root.from) {
                root.from[root.bind] = !root.from[root.bind];
            }
        }
    }

    Component.onCompleted: {
        root.checked = Qt.binding(function() { return root.from[root.bind]; });
    }
}
