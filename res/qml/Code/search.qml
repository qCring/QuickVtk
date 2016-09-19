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

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 1;
        color: "#181A1F";
    }

    Column {
        id: column;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 8;
        anchors.rightMargin: 8;

        topPadding: 4;
        spacing: 4;

        Lib.Label {
            text: "Find & Replace"
        }

        Item {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: searchInput.height + 4;

            Lib.Label {
                id: searchLabel;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;

                text: "Find";
            }

            SearchInput {
                id: searchInput;

                refocus: root.refocus;

                anchors.left: searchLabel.right;
                anchors.right: parent.right;
                anchors.leftMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;
            }
        }
    }
}
