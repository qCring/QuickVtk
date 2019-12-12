import QtQuick 2.12

import App 1.0 as App

TextInput {
    id: root;

    property var refocus;

    property alias radius: rect.radius;
    property alias background: rect.color;

    property color borderDefault: "#181A1F"
    property color borderActive: "#9DA5B4"

    leftPadding: 4;
    rightPadding: 4;

    color: enabled ? "#fff" : "#9DA5B4";
    selectedTextColor: "#000";
    selectionColor: root.borderActive;

    font.family: "Roboto";
    font.pointSize: 13;
    verticalAlignment: TextInput.AlignVCenter;

    activeFocusOnPress: true;
    selectByMouse: true;
    clip: true;

    signal enterPressed();

    Rectangle {
        id: rect;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        z: parent.z - 1;
        height: root.contentHeight;

        color: "#333842"
        border.color: root.activeFocus ? root.borderActive : root.borderDefault;
    }

    Keys.onPressed: {
        var key = event.key;

        if (key == Qt.Key_Escape) {
            context.editor.search.visible = false;
            event.accepted = true;
            refocus.forceActiveFocus();
        }
        else if (key == Qt.Key_Enter || key == Qt.Key_Return) {
            enterPressed();
            event.accepted = true;
        }
    }
}
