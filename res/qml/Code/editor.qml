import QtQuick 2.6
import QtQuick.Controls 1.4

import App 1.0 as App
import Lib 1.0 as Lib

Item {
    id: root;

    property var editor: App.editor;

    clip: true;

    function activate() {
        textEdit.forceActiveFocus();
    }

    Flickable {
        id: flickable;

        anchors.left: lines.right;
        anchors.top: parent.top;
        anchors.bottom: search.visible ? search.top : footer.top;
        anchors.right: parent.right;

        contentWidth: textEdit.width;
        contentHeight: textEdit.height;

        boundsBehavior: Flickable.StopAtBounds

        function updateScrollX(x) {
            if (contentX >= x) {
                contentX = x;
            } else if (contentX + width <= x) {
                contentX = x + 1 - width;
            }
        }

        function updateScrollY(y) {
            if (contentY >= y) {
                contentY = y;
            } else if (contentY + height <= y + textEdit.cursorHeight) {
                contentY = y + textEdit.cursorHeight - height;
            }
        }

        Rectangle {
            id: cursorBg;

            anchors.left: parent.left;
            anchors.right: parent.right;

            y: textEdit.cursorY;
            height: textEdit.cursorHeight;

            color: "#2C303A"
        }

        Repeater {
            model: App.editor.errors;

            delegate: Error {
                anchors.left: parent.left;
                anchors.right: parent.right;

                height: textEdit.cursorHeight;
                y: (model.line - 1) * height;

                error: model;
            }
        }

        Lib.TextEdit {
            id: textEdit

            width: Math.max(implicitWidth, root.width - lines.width);
            leftPadding: 4;

            property int cursorX: cursorRectangle.x;
            property int cursorY: cursorRectangle.y;
            property int cursorHeight: cursorRectangle.height;
            property bool showCursor: true;

            onActiveFocusChanged: {
                if (activeFocus) {
                    activateCursor();
                } else {
                    deactivateCursor();
                }
            }

            onCursorXChanged: {
                activateCursor();
                flickable.updateScrollX(cursorX);
            }

            onCursorYChanged: {
                activateCursor();
                flickable.updateScrollY(cursorY);
            }

            font.pointSize: editor.fontSize;

            Keys.onPressed: event.accepted = editor.onKeyPressed(event.key, event.modifiers, event.text);

            cursorDelegate: Rectangle {
                id: cursorDel;

                width: 1;
                color: "#fff";
                visible: textEdit.showCursor;
            }

            function activateCursor() {
                textEdit.showCursor = true;
                cursorTimer.restart();
            }

            function deactivateCursor() {
                textEdit.showCursor = false;
                cursorTimer.stop();
            }

            Timer {
                id: cursorTimer;

                interval: App.settings.cursorFlashTime;
                running: true;
                repeat: true;

                onTriggered: textEdit.showCursor = !textEdit.showCursor;
            }
        }
    }

    Rectangle {
        id: lines;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: footer.top;

        width: linesCol.width + lineBar.width;
        color: "#21252B"

        Column {
            id: linesCol;

            y: -flickable.contentY;

            Repeater {
                model: textEdit.lineCount;

                delegate: Text {
                    anchors.right: parent.right;
                    rightPadding: 8;
                    leftPadding: 8;

                    font.family: textEdit.font.family;
                    font.pointSize: editor.fontSize;
                    verticalAlignment: Text.AlignVCenter;

                    color: index >= editor.regionStart && index <= editor.regionEnd ? "#fff" : "#6E7582"
                    text: index + 1;
                }
            }
        }

        Item {
            id: lineBar;

            anchors.top: linesCol.top;
            anchors.bottom: parent.bottom;
            anchors.left: linesCol.right;

            width: 14;

            Column {
                Repeater {
                    model: editor.lines.length;
                    delegate: Item {
                        width: 14;
                        height: textEdit.cursorHeight;

                        Rectangle {
                            anchors.fill: parent;
                            color: "#9DA5B4"
                            opacity: Math.round(editor.lines[index] / 2)/20;
                        }

                        Lib.Label {
                            anchors.centerIn: parent;
                            font.pointSize: 8;
                            color: "#fff";
                            text: editor.lines[index];
                        }
                    }
                }
            }
        }

        Rectangle {
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;

            width: 1;
            color: "#343842"
        }

        Rectangle {
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: lineBar.left;

            width: 1;
            color: "#343842"
        }
    }

    Search {
        id: search;

        anchors.left: parent.left;
        anchors.bottom: footer.top;
        anchors.right: parent.right;

        refocus: textEdit;
    }

    Footer {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }

    Connections {
		target: editor;
		onUpdateSelection: textEdit.select(editor.selectionStart, editor.selectionEnd);
	}

    Component.onCompleted: {
        editor.document       = textEdit.textDocument;
        editor.selectionStart = Qt.binding(function() { return textEdit.selectionStart; });
        editor.selectionEnd   = Qt.binding(function() { return textEdit.selectionEnd; });
        textEdit.forceActiveFocus();
    }
}
