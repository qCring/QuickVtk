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

                font.bold: true;

                text: "Find & Replace"
            }

            Lib.TagLabel {
                id: matchLabel;

                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;

                label.leftPadding: 4;
                label.rightPadding: 4;

                color: "#2B68A4"
                visible: App.search.matchCount;

                label.text: App.search.matchCount > 0 ? (App.search.currentMatch + 1) + " of " + App.search.matchCount : "";
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
                anchors.rightMargin: 4;
                anchors.verticalCenter: parent.verticalCenter;

                KeyNavigation.tab: replaceInput;
                KeyNavigation.backtab: replaceInput;

                refocus: root.refocus;
                onTextChanged: App.search.findString = text;

                onEnterPressed: {
                    App.search.findNext();
                }

                Lib.Label {
                    anchors.right: parent.right;
                    anchors.rightMargin: 4;
                    anchors.verticalCenter: parent.verticalCenter;

                    font.pointSize: 10;
                    text: App.search.regexError;
                }
            }

            Lib.Button {
                id: findButton;

                anchors.right: findOptions.left;
                anchors.rightMargin: 4;
                anchors.verticalCenter: parent.verticalCenter;

                label.text: "Find";

                icon.type: icon.types.fa_search;
                width: replaceButton.width;

                onClicked: {
                    App.search.findString = findInput.text;
                    findInput.forceActiveFocus();
                }
            }

            Row {
                id: findOptions;

                anchors.right: parent.right;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;

                Lib.Button {
                    anchors.verticalCenter: parent.verticalCenter;

                    highlight: App.search.caseSensitive;
                    width: replaceAllButton.width/2;

                    label.text: "Aa";

                    onClicked: {
                        App.search.caseSensitive = !App.search.caseSensitive;
                        findInput.forceActiveFocus();
                    }
                }

                Lib.Button {
                    anchors.verticalCenter: parent.verticalCenter;

                    highlight: App.search.useRegex;
                    width: replaceAllButton.width/2;

                    label.text: ".*";

                    onClicked: {
                        App.search.useRegex = !App.search.useRegex;
                        findInput.forceActiveFocus();
                    }
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
                anchors.right: replaceButtons.left;
                anchors.rightMargin: 4;
                anchors.verticalCenter: parent.verticalCenter;

                KeyNavigation.tab: findInput;
                KeyNavigation.backtab: findInput;

                refocus: root.refocus;

                onTextChanged: App.search.replaceString = text;

                onEnterPressed: {
                    App.search.replaceNext();
                }
            }

            Row {
                id: replaceButtons;

                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: parent.right;

                spacing: 4;

                Lib.Button {
                    id: replaceButton;

                    anchors.verticalCenter: parent.verticalCenter;

                    label.text: "Replace";
                    icon.type: icon.types.fa_refresh;

                    onClicked: {
                        App.search.replaceNext();
                        replaceInput.forceActiveFocus();
                    }
                }

                Lib.Button {
                    id: replaceAllButton;

                    anchors.verticalCenter: parent.verticalCenter;

                    label.text: "Replace All";
                    icon.type: icon.types.fa_refresh;

                    enabled: false;

                    onClicked: {
                        App.search.replaceAll();
                        replaceInput.forceActiveFocus();
                    }
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
