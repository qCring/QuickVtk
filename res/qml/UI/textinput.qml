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

  property color borderDefault: "#181A1F"
  property color borderActive: "#9DA5B4"

  color: enabled ? "#fff" : "#9DA5B4";
  selectionColor: "#aa4D69A8";

  font.family: "Roboto";
  font.pointSize: 13;
  verticalAlignment: TextInput.AlignVCenter;

  leftPadding: 4;
  rightPadding: 4;

  activeFocusOnPress: true;
  selectByMouse: true;
  clip: true;

  Rectangle {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
    height: 1;
    color: root.activeFocus ? "#9DA5B4" : "#6E7582";
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
