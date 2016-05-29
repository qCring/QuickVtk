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

    Row {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: 4;

        spacing: 4;

        Lib.TagLabel {
            anchors.verticalCenter: parent.verticalCenter;
            visible: App.compiler.source.length > 0;
            color: App.compiler.modified ? "#aa5511" : "#008800";
            label.text: App.compiler.modified ? "modified" : "up-to-date";
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            font.pixelSize: 11;
            text: App.compiler.fileName;
        }
    }
}
