import QtQuick 2.5

Rectangle {
    id: root;

    width: row.width + 24;
    height: label.height + 6;

    property alias label: label;
    property alias icon: icon;

    color: ma.pressed ? "#0289FF" : ma.containsMouse ? "#363C46" : "#333842"
    border.color: "#181A1F"

    radius: 2;

    signal clicked;

    Row {
        id: row;

        anchors.centerIn: parent;

        spacing: 4;

        Icon {
            id: icon;

            anchors.verticalCenter: parent.verticalCenter;

            color: label.color;
        }

        Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;

            font.weight: Font.Medium;
            color: enabled ? ma.containsMouse ? "#fff" : "#9DA5B4" : "#6E7582";
        }
    }

    MouseArea {
        id: ma;

        anchors.fill: parent;

        hoverEnabled: true;
        onClicked: root.clicked();
    }
}
