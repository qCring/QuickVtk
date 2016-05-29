import QtQuick 2.5

Rectangle {
    id: root;

    width: label.width + 24;
    height: label.height + 6;

    property alias label: label;

    color: ma.pressed ? "#0289FF" : ma.containsMouse ? "#363C46" : "#333842"
    border.color: "#181A1F"

    radius: 2;

    signal clicked;

    Label {
        id: label;

        anchors.centerIn: parent;
        font.weight: Font.Medium;
        color: ma.containsMouse ? "#fff" : "#9DA5B4"
    }

    MouseArea {
        id: ma;

        anchors.fill: parent;

        hoverEnabled: true;
        onClicked: root.clicked();
    }
}
