import QtQuick 2.6
import QtQuick.Controls 1.4

import App 1.0 as App
import Lib 1.0 as Lib

Rectangle {
    id: root;

    property var editor: Controllers.editor;

    clip: true;

    color: "#181A1F"

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

            color: "#21252B"
        }

        Repeater {
            model: Controllers.editor.errors;

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

            readOnly: true;

            width: Math.max(implicitWidth, root.width - lines.width);
            height: Math.max(implicitHeight, root.height - footer.height);

            leftPadding: 4;

            property bool multiSelection: editor.selection.startLine != editor.selection.endLine;
            property int cursorX: cursorRectangle.x;
            property int cursorY: cursorRectangle.y;
            property int cursorHeight: cursorRectangle.height;
            property bool showCursor: true;

            font.pointSize: editor.fontSize;

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

            cursorDelegate: Rectangle {
                id: cursorDel;

                width: 1.5;
                color: "orange";
                visible: textEdit.showCursor && !textEdit.multiSelection;
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

                interval: Controllers.settings.cursorFlashTime;
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

        color: "#181A1F"

        width: linesCol.width + 4;

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

                    color: index  >= editor.selection.startLine && index <= editor.selection.endLine ? "#fff" : "#6E7582"
                    text: index + 1;
                }
            }
        }

        Rectangle {
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.right: parent.right;

            width: 1;
            color: "#21252B"
        }
    }

    Search {
        id: search;

        anchors.left: parent.left;
        anchors.bottom: footer.top;
        anchors.right: parent.right;

        refocus: textEdit;
    }

    MouseArea {
        anchors.fill: parent;
        enabled: !textEdit.activeFocus;

        onClicked: {
            root.activate();
        }
    }

    Footer {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }

    Connections {
        target: editor;
        onClear: textEdit.clear();
    }

    Connections {
        target: editor;
        onSelect: textEdit.select(start, end);
    }

    Component.onCompleted: {
        editor.document = textEdit.textDocument;
        editor.selection.startPosition = Qt.binding (function() { return textEdit.selectionStart; });
        editor.selection.endPosition = Qt.binding (function() { return textEdit.selectionEnd; });
        textEdit.forceActiveFocus();
    }
}
