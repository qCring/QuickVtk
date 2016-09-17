import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    property var refocus;

    height: column.height;
    color: "#21252B"

    visible: App.search.visible;

    onVisibleChanged: {
        if (visible) {
            searchInput.forceActiveFocus();
        }
    }

    Column {
        id: column;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.margins: 8;

        Lib.TextInput {
            id: searchInput;

            refocus: root.refocus;
            immediate: true;
            from: App.search; bind: "searchString";

            anchors.left: parent.left;
            anchors.right: parent.right;

            onActiveFocusChanged: {
                if (!activeFocus) {
                    App.search.visible = false;
                }
            }
        }
    }
}
