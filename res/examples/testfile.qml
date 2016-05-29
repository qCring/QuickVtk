import QtQuick 2.5

Rectangle {
    color: "#282C34"

    Header {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Lib.Label {
        anchors.centerIn: parent;

        color: "#fff"
        text: App.compiler.source;
    }

    Footer {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
