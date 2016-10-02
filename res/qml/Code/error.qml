import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Item {
    id: root;

    property var error: undefined;

    Lib.Icon {
        id: ic;

        anchors.right: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.rightMargin: 4;

        color: "#ff0000"
        type: types.fa_caret_right;
        pointSize: App.editor.fontSize;
    }

    Lib.TagLabel {
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        label.text: error.message;
        label.font.pointSize: ic.pointSize - 3;
        label.leftPadding: 4;
        label.rightPadding: 4;

        color: "#B70F11"
        border.color: "#00000000";
    }
}
