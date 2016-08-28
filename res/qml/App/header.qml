import QtQuick 2.6

import Lib 1.0 as Lib
import TypeInfo 1.0 as TypeInfo

Rectangle {
    height: visible ? 32 : 0;
    visible: !App.expanded;

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

            label.text: "Open";
            icon.type: icon.types.fa_folder_open;

            onClicked: App.editor.openFile();
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            label.text: "Run";
            icon.type: icon.types.fa_play_circle;

            onClicked: {
                App.editor.run();
            }
        }
    }

    Row {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: 4;

        spacing: 4;

        TypeInfo.Search {
            anchors.verticalCenter: parent.verticalCenter;
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            icon.type: icon.types.fa_expand;
            onClicked: App.expanded = true;

            color: "#00000000"
            border.color: "#00000000"
        }
    }
}
