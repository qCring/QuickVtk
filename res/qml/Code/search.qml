import QtQuick 2.12

import Lib 1.0 as Lib
import App 1.0 as App

Rectangle {
    id: root;

    property var refocus;
    property var controller: context.editor.search;

    height: column.height;
    color: "#21252B"

    visible: controller.visible;

    onVisibleChanged: {
        if (visible) {
            findInput.forceActiveFocus();
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

                //label.leftPadding: 4;
                //label.rightPadding: 4;

                color: "#2B68A4"
                visible: controller.matchCount;

                label.text: controller.matchCount > 0 ? (controller.currentMatch + 1) + " of " + controller.matchCount : "";
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
                onTextChanged: controller.findString = text;

                onEnterPressed: {
                    controller.findNext();
                }

                Lib.Label {
                    anchors.right: parent.right;
                    anchors.rightMargin: 4;
                    anchors.verticalCenter: parent.verticalCenter;

                    font.pointSize: 10;
                    text: controller.regexError;
                }
            }

            Lib.Button {
                id: findButton;

                anchors.right: findOptions.left;
                anchors.rightMargin: 4;
                anchors.verticalCenter: parent.verticalCenter;

                label.text: "Find";

                icon: icons.fa_search;
                width: replaceButton.width;

                onClicked: {
                    controller.findString = findInput.text;
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

                    highlight: controller.caseSensitive;
                    width: replaceAllButton.width/2;

                    label.text: "Aa";

                    onClicked: {
                        controller.caseSensitive = !controller.caseSensitive;
                        findInput.forceActiveFocus();
                    }
                }

                Lib.Button {
                    anchors.verticalCenter: parent.verticalCenter;

                    highlight: controller.useRegex;
                    width: replaceAllButton.width/2;

                    label.text: ".*";

                    onClicked: {
                        controller.useRegex = !controller.useRegex;
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

                onTextChanged: controller.replaceString = text;

                onEnterPressed: {
                    controller.replaceNext();
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
                    icon: icons.fa_refresh;

                    onClicked: {
                        controller.replaceNext();
                        replaceInput.forceActiveFocus();
                    }
                }

                Lib.Button {
                    id: replaceAllButton;

                    anchors.verticalCenter: parent.verticalCenter;

                    label.text: "Replace All";
                    icon: icons.fa_refresh;

                    enabled: false;

                    onClicked: {
                        controller.replaceAll();
                        replaceInput.forceActiveFocus();
                    }
                }
            }
        }
    }
}
