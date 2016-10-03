import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    property var error: undefined;

    color: "#782A32";

    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        width: 2;
        color: "#ff0000"
    }

    Lib.TagLabel {
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        label.text: error.message;
        label.font.pointSize: App.editor.fontSize - 2;
        label.leftPadding: 4;
        label.rightPadding: 4;

        color: "#181A1F"
        border.color: root.color;
    }
}
