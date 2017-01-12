import QtQuick 2.6

import Lib 1.0 as Lib

Rectangle {
    height: visible ? 24 : 0;
    visible: !App.expanded;

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

        spacing: 4;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_circle;
            color: App.editor.modified ? "#ff8800" : "#00ff00";
            // visible: App.editor.document.fileName > 0 && App.editor.modified;
            pointSize: 6;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: App.editor.fileUrl.length > 0 ? App.editor.fileUrl : "untitled"
            font.pointSize: 12;
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
            type: types.fa_bug;
            visible: App.debugBuild;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            text: "version " + App.version;
        }
    }
}
