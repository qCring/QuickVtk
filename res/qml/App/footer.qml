import QtQuick 2.6

import Lib 1.0 as Lib

Rectangle {
    height: visible ? 24 : 0;
    visible: !Controllers.expanded;

    color: "#21252B"

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 1;

        color: "#181A1F"
    }

    Row {
        id: fileNameRow;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.leftMargin: 8;

        spacing: 8;

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: Controllers.editor.modified ? "modified" : "up-to-date";
            color: Controllers.editor.modified ? "#ff8800" : "#00ff00";
            visible: Controllers.editor.fileUrl.length > 0;
            font.pointSize: 10;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: Controllers.editor.fileUrl.length > 0 ? Controllers.editor.fileUrl : ""
            font.pointSize: 10;
        }
    }

    Row {
        id: dbgRow;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: 4;

        spacing: 4;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;
            icon: icons.fa_bug;
            visible: Controllers.debugBuild;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            text: "version " + Controllers.version;
        }
    }
}
