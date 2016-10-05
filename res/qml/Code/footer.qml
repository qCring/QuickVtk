import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    height: 20;

    color: "#21252B"

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

            onClicked: App.editor.incrementFontSize();
        }

        Lib.Button {
            anchors.verticalCenter: parent.verticalCenter;

            frameless: true;
            icon.font.pointSize: 12;
            icon.type: icon.types.fa_search_minus;

            onClicked: App.editor.decrementFontSize();
        }
    }

}
