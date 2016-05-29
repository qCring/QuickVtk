import QtQuick 2.5

import "./lib" as Lib

Rectangle {
    height: 32;
    color: "#21252B"

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        height: 1;

        color: "#181A1F"
    }

    Lib.Button {
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 4;

        label.text: "Open File";

        onClicked: App.compiler.openFile();
    }

    Lib.Label {
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        text: App.compiler.fileName;
    }
}
