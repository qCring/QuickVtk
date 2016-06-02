import QtQuick 2.6

Rectangle {
    id: root;

    width: label.width + 8;
    height: label.height + 4;

    property alias label: label;

    color: "#008800";
    border.color: "#181A1F"

    radius: 2;

    Label {
        id: label;

        anchors.centerIn: parent;
        font.weight: Font.Medium;
        font.pixelSize: 11;
        color: "#fff"
    }
}
