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

            SearchInput {
                id: findInput;

                anchors.left: parent.left;
                anchors.right: findButton.left;
                anchors.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                KeyNavigation.tab: replaceInput;
                KeyNavigation.backtab: replaceInput;

                refocus: root.refocus;
                onTextChanged: App.search.findString = text;

                onEnterPressed: {
                    App.search.findNext();
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

        Item {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: replaceInput.height + 4;

            SearchInput {
                id: replaceInput;

                anchors.left: parent.left;
                anchors.right: replaceButton.left;
                anchors.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;

                KeyNavigation.tab: findInput;
                KeyNavigation.backtab: findInput;

                refocus: root.refocus;

                onTextChanged: App.search.replaceString = text;

                onEnterPressed: {
                    App.search.replaceNext();
                }
            }

            Lib.Button {
                id: replaceButton;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                label.text: App.search.matchCount > 0 ? "Replace" : "Replace";

                onClicked: {
                    App.search.replaceNext();
                    replaceInput.forceActiveFocus();
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
