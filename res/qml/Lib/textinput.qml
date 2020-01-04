import QtQuick 2.12

TextInput {
    id: root;

    property var refocus;
    property var from;

    property string bind;
    property string lastInput;
    property string newInput;

    property bool immediate: false;
    property bool resetInput: false;
    property bool clearFocusOnEnter: true;

    property alias radius: rect.radius;
    property alias background: rect.color;

    property color borderDefault: "#181A1F"
    property color borderActive: "#9DA5B4"

    leftPadding: 4;
    rightPadding: 4;

    color: enabled ? "#fff" : "#9DA5B4";
    selectionColor: "#aa4D69A8";

    font.family: "Roboto";
    font.pointSize: 13;
    verticalAlignment: TextInput.AlignVCenter;

    activeFocusOnPress: true;
    selectByMouse: true;
    clip: true;

    Rectangle {
        id: rect;

        anchors.fill: parent;

        z: parent.z - 1;

        color: "#333842"
        border.color: root.activeFocus ? root.borderActive : root.borderDefault;
    }

    onActiveFocusChanged: {
        if (activeFocus) {
            root.lastInput = text;
        } else {
            if (root.resetInput) {
                applyText(newInput);
            } else {
                applyText(text);
            }
        }
    }

    onTextChanged: {
        if (root.immediate) {
            applyText(text);
        }
    }

    function applyText(newText) {
        if (root.from) {
            text = newText;
            root.from[root.bind] = newText;
        }
    }

    function clearFocus() {
        if (refocus) {
            refocus.forceActiveFocus();
        } else {
            root.parent.forceActiveFocus();
        }
    }

    Keys.onPressed: {
        var key = event.key;

        if (key == Qt.Key_Escape) {
            newInput = root.resetInput ? lastInput : text;
            event.accepted = true;
            clearFocus();
        }
        else if (key == Qt.Key_Enter || key == Qt.Key_Return) {
            newInput = text;
            event.accepted = true;

            if (clearFocusOnEnter) {
                clearFocus();
            }
        }
    }
}
