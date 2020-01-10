import QtQuick 2.12
import QtQuick.Controls 2.12

import UI 1.0 as UI

Item {
    id: root;

    property var file: App.document.file;

    clip: true;

    Flickable {
        id: _flickable;

        anchors.left: _lines.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        contentWidth: _textEdit.width;
        contentHeight: _textEdit.height;

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
            } else if (contentY + height <= y + _textEdit.cursorHeight) {
                contentY = y + _textEdit.cursorHeight - height;
            }
        }

        Rectangle {
            anchors.left: parent.left;
            anchors.right: parent.right;

            y: _textEdit.cursorY;
            height: _textEdit.cursorHeight;

            color: "#2D313C"
        }

        Repeater {
          model: file != undefined ? file.errors : null;

          delegate: Rectangle {
            id: root;

            anchors.left: parent.left;
            anchors.right: parent.right;

            height: _textEdit.cursorHeight;
            y: (Math.max(model.line - 1, 0)) * height;
            color: "#22C54632";

            UI.Icon {
              anchors.verticalCenter: parent.verticalCenter;
              anchors.right: parent.left;

              icon: icons.fa_chevron_right;
              color: "#933628";
              iconSize: _textEdit.font.pointSize;
            }

            Rectangle {
              anchors.right: parent.right;
              anchors.top: parent.top;
              anchors.bottom: parent.bottom;
              anchors.rightMargin: 2;

              width: _error.width + 16;
              radius: 2;
              color: "#933628"

              UI.Icon {
                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: parent.left;

                icon: icons.fa_caret_left;
                color: "#933628";
                iconSize: _textEdit.font.pointSize;
              }

              Row {
                id: _error;

                anchors.centerIn: parent;
                spacing: 8;

                UI.Icon {
                  anchors.verticalCenter: parent.verticalCenter;
                  icon: icons.fa_exclamation_circle;
                  iconSize: _textEdit.font.pointSize - 1;
                  color: "#fff";
                }

                UI.Label {
                  anchors.verticalCenter: parent.verticalCenter;
                  font.pointSize: _textEdit.font.pointSize;
                  text: model.message;
                  color: "#fff"
                }
              }
            }
          }
        }


        TextEdit {
            id: _textEdit;

            readOnly: true;
            font.family: "Bitstream Vera Sans Mono";

            selectByMouse: true
            mouseSelectionMode: TextEdit.SelectCharacters
            selectionColor: "#aa4D69A8"
            color: "#fff"

            textFormat: TextEdit.PlainText
            wrapMode: TextEdit.NoWrap

            width: Math.max(implicitWidth, root.width - _lines.width);
            height: Math.max(implicitHeight, root.height);

            leftPadding: 4;

            property int cursorX: cursorRectangle.x;
            property int cursorY: cursorRectangle.y;
            property int cursorHeight: cursorRectangle.height;
            property bool showCursor: true;

            font.pointSize: 12;
            text: file != undefined ? file.content : "";

            onCursorXChanged: {
                _flickable.updateScrollX(cursorX);
            }

            onCursorYChanged: {
                _flickable.updateScrollY(cursorY);
            }

            cursorDelegate: Rectangle {
                width: 1.5;
                color: "orange";
                visible: _textEdit.showCursor;
            }
        }
    }

    Item {
        id: _lines;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;

        width: _linesCol.width + 4;

        Column {
            id: _linesCol;

            y: -_flickable.contentY;

            Repeater {
                model: _textEdit.lineCount;

                delegate: Text {
                    anchors.right: parent.right;
                    rightPadding: 8;
                    leftPadding: 8;

                    font.family: _textEdit.font.family;
                    font.pointSize: _textEdit.font.pointSize;

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
