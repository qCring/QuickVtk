import QtQuick 2.12

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    height: 22;

    color: "#21252B"


    Lib.Label {
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        

        text: (context.editor.selection.startLine + 1) + ":" + (context.editor.selection.startColumn + 1);
        font.pointSize: 12;
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        spacing: 12;

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;
            icon: icons.fa_info_circle;
            color: "#ffa500"
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            
            font.pointSize: 10;
            text: "read-only";
            color: "#ffa500"
        }
    }

    Row {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.rightMargin: 8;

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            frameless: true;
            iconSize: 12;
            icon: icons.fa_search_plus;

            onClicked: context.editor.increaseFontSize();
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            frameless: true;
            iconSize: 12;
            icon: icons.fa_search_minus;

            onClicked: context.editor.decreaseFontSize();
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
