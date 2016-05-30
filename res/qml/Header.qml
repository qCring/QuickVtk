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

    Row {
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        spacing: 4;

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            label.text: "Open File";
            icon.type: icon.types.fa_folder_open;

            onClicked: App.compiler.openFile();
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            label.text: "Compile";
            icon.type: icon.types.fa_play_circle;
            enabled: App.compiler.modified;

            onClicked: {
                App.compiler.updateSource();
                App.compiler.compile();
            }
        }

        Lib.CheckBox {
            anchors.verticalCenter: parent.verticalCenter;

            label.text: "Auto-Compile"
            checked: App.compiler.autocompile;

            onClicked: App.compiler.autocompile = !App.compiler.autocompile;
        }
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
