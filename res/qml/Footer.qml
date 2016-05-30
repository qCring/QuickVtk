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

    Row {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.leftMargin: 4;

        spacing: 8;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: App.compiler.failed ? types.fa_exclamation_circle : types.fa_check_circle;
            color: App.compiler.ready ? App.compiler.failed ? "#ff0000" : "#00ff00" : "#6E7582";
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;

            text: App.compiler.ready ? App.compiler.failed ? "compilation failed" : "compilation successful" : "no file to compile";
        }
    }

    Row {
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
