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
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.leftMargin: 8;

        spacing: 4;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_circle;
            color: "#ff8800";
            visible: App.editor.filePath.length > 0 && App.editor.modified;
            pointSize: 6;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: App.editor.filePath.length > 0 ? App.editor.filePath : "untitled"
            font.pointSize: 11;
        }
    }

    Row {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: dbgRow.left;
        anchors.rightMargin: 12;

        spacing: 4;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_exclamation_circle;
            color: App.notifications.errorCount > 0 ? "#ff0000" : "#9DA5B4"
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: App.notifications.errorCount;
            font.pointSize: 11;
        }

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_exclamation_triangle;
            color: App.notifications.warningCount > 0 ? "#ff9900" : "#9DA5B4"
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: App.notifications.warningCount;
            font.pointSize: 11;
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
