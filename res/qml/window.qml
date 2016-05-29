import QtQuick 2.5

import "./lib" as Lib

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
        text: "QuickVtk"
    }

    Footer {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
