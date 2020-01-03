import QtQuick 2.12
import QtQuick.Controls 2.12

import Lib 1.0 as Lib

Item {
    id: root;

    property var file: App.document.file;

    clip: true;

    Flickable {
        id: flickable;

        anchors.left: lines.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
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

            color: "#2D313C"
        }

        Repeater {
          model: file != undefined ? file.errors : null;

          delegate: Rectangle {
            id: root;

            anchors.left: parent.left;
            anchors.right: parent.right;

            height: textEdit.cursorHeight;
            y: (model.line) * height;

            color: "#C54632";

            Rectangle {
              anchors.left: parent.left;
              anchors.top: parent.top;
              anchors.bottom: parent.bottom;

              width: 2;
              color: "#ff0000"
            }

            Lib.Badge {
              anchors.right: parent.right;
              anchors.top: parent.top;
              anchors.bottom: parent.bottom;

              label.text: model.message;

              color: "#181A1F"
              border.color: root.color;
            }
          }
        }


        TextEdit {
            id: textEdit

            readOnly: true;
            font.family: "Bitstream Vera Sans Mono";

            selectByMouse: true
            mouseSelectionMode: TextEdit.SelectCharacters
            selectionColor: "#aa4D69A8"
            color: "#fff"

            textFormat: TextEdit.PlainText
            wrapMode: TextEdit.NoWrap

            width: Math.max(implicitWidth, root.width - lines.width);
            height: Math.max(implicitHeight, root.height);

            leftPadding: 4;

            property int cursorX: cursorRectangle.x;
            property int cursorY: cursorRectangle.y;
            property int cursorHeight: cursorRectangle.height;
            property bool showCursor: true;

            font.pointSize: 12;
            text: file != undefined ? file.content : "";

            onCursorXChanged: {
                flickable.updateScrollX(cursorX);
            }

            onCursorYChanged: {
                flickable.updateScrollY(cursorY);
            }

            cursorDelegate: Rectangle {
                id: cursorDel;

                width: 1.5;
                color: "orange";
                visible: textEdit.showCursor;
            }
        }
    }

    Item {
        id: lines;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

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
                    font.pointSize: textEdit.font.pointSize;

                    verticalAlignment: Text.AlignVCenter;

                    color: "#6E7582"
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
}
