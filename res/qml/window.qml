import QtQuick 2.5

Rectangle {
    color: "#282C34"

    Text {
        anchors.centerIn: parent;

        color: "#fff"
        text: "QuickVtk"
    }

    Footer {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
