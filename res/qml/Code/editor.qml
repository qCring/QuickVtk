import QtQuick 2.6

import App 1.0 as App
import Lib 1.0 as Lib

Item {
    id: root;

    property var editor: App.editor;

    clip: true;

    function activate() {
        textEdit.forceActiveFocus();
    }

    onVisibleChanged: {
        if (visible) {
            activate();
        }
    }

    Item {
        anchors.fill: parent;

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                root.activate();
            }
        }

        Rectangle {
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            width: editor.fontSize * 3;
            color: "#21252B";

            Rectangle {
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                anchors.right: parent.right;
                width:1;

                color: "#181A1F"
            }
        }

        Lib.TextEdit {
            id: textEdit

            y: -scrollView.flickableItem.contentY;

            anchors.leftMargin: lines.width + 4;
            anchors.left: parent.left;
            anchors.right: parent.right;
            font.pointSize: editor.fontSize;

            Keys.onPressed: event.accepted = editor.onKeyPressed(event.key, event.modifiers, event.text);

            Rectangle {
                id: cursorBg;

                anchors.left: parent.left;
                anchors.right: parent.right;
                y: height * editor.line;
                height: textEdit.cursorRectangle.height;

                color: "#11ddddff"
            }
        }

        Lib.ScrollView {
            id: scrollView;

            anchors.fill: parent;

            Column {
                id: lines;

                width: editor.fontSize * 3;

                Repeater {
                    model: textEdit.lineCount;

                    delegate: Text {
                        width: lines.width;
                        textFormat:             Text.PlainText;
                        style:                  Text.Normal;
                        color:                  index == editor.line ? "#fff" : "#4B5363"
                        font.family:            textEdit.font.family;
                        font.pixelSize:         editor.fontSize;
                        verticalAlignment:      Text.AlignVCenter;
                        horizontalAlignment:    Text.AlignHCenter;

                        text: index + 1;
                    }
                }
            }
        }
    }

    Issues {
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;
    }

    Search {
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;

        refocus: textEdit;
    }

    Connections {
		target: editor;
		onUpdateSelection: textEdit.select(editor.selectionStart, editor.selectionEnd);
        onFontSizeChanged: {
            cursorBg.y = textEdit.positionToRectangle(textEdit.position).y;
            cursorBg.height = textEdit.cursorRectangle.height;
            cursorBg.y = Qt.binding(function() { return textEdit.cursorRectangle.y; });
        }
	}

    Component.onCompleted: {
        editor.document       = textEdit.textDocument;
        editor.selectionStart = Qt.binding(function() { return textEdit.selectionStart; });
        editor.selectionEnd   = Qt.binding(function() { return textEdit.selectionEnd; });
        textEdit.forceActiveFocus();
    }
}
