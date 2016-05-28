import QtQuick 2.5

import "./lib" as Lib

Rectangle {
    height: 24;
    color: "#21252B"

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 1;

        color: "#181A1F"
    }

    Lib.Label {
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.margins: 4;
        text: "version " + App.version;
        color: "#fff"
    }
}
