import QtQuick 2.6

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    property var refocus;

    height: column.height;
    color: "#21252B"

    visible: false;

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

        bottomPadding: 4;
        topPadding: 4;
        spacing: 4;

        Item {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: titleLabel.height + 4;

            Lib.Label {
                id: titleLabel;

                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;

                text: "Find & Replace"
            }

            Lib.Label {
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;

                text: App.search.matchCount > 0 ? (App.search.currentMatch + 1) + "/" + App.search.matchCount : "";
            }
        }

        Item {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: findInput.height + 4;

            Lib.Label {
                id: findLabel;
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;

                text: "Find";
            }

            SearchInput {
                id: findInput;

                refocus: root.refocus;

                anchors.left: findLabel.right;
                anchors.right: findButton.left;
                anchors.leftMargin: 8;
                anchors.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                onInputFinished: {
                    App.search.findString = input;
                }
            }

            Lib.Button {
                id: findButton;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                label.text: App.search.matchCount > 0 ? "Next" : "Find";

                onClicked: {
                    App.search.findString = findInput.text;
                    findInput.forceActiveFocus();
                }
            }
        }
    }

    Connections {
        target: App.search;
        onShow: {
            root.visible = true;
            findInput.forceActiveFocus();
        }
        onHide: { root.visible = false; }
    }
}
