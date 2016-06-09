import QtQuick 2.5

Rectangle {
    color: "#444"

    anchors.fill: parent;

    Text {
        anchors.centerIn: parent;
        font.pointSize: 40;
        color: "#fff"
        text: "yay, i was compiled at runtime!"
    }
}
