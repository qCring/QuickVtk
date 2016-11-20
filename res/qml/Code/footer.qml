import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    height: 22;

    color: "#21252B"

    Lib.Label {
        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 4;
        visible: App.editor.formatTime > 0;
        text: App.editor.formatTime < 1000 ? "time needed for formatting: " + App.editor.formatTime + " ms" : "time needed for formatting: " + App.editor.formatTime/1000 + " sec";
        color: "orange"
        font.pointSize: 10;
    }

    Row {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: 8;

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            frameless: true;
            icon.font.pointSize: 12;
            icon.type: icon.types.fa_search_plus;

            onClicked: App.editor.increaseFontSize();
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            frameless: true;
            icon.font.pointSize: 12;
            icon.type: icon.types.fa_search_minus;

            onClicked: App.editor.decreaseFontSize();
        }
    }

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 1;
        color: "#181A1F"
    }
}
