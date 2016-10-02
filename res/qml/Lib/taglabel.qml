import QtQuick 2.6

Rectangle {
    id: root;

    width: label.width;
    height: label.height;

    property alias label: label;

    color: "#008800";
    border.color: "#181A1F"

    radius: 2;

    Label {
        id: label;

        anchors.centerIn: parent;
        font.weight: Font.Medium;
        font.pointSize: 11;

        padding: 1;
        color: "#fff"
    }
}
