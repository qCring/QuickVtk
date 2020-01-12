import QtQuick 2.12
import UI 1.0 as UI

Item {
  id: root;

  property alias controls: _controls;
  property var file: App.document.file;
  property var hasErrors: file ? file.errors.length > 0 : false;

  Column {
    id: _outer;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    spacing: 8;

    UI.List {
      title: "File"

      UI.Label {
        anchors.left: parent.left;
        anchors.right: parent.right;
        text: file ? file.title : "No file selected";
      }

      UI.Label {
        anchors.left: parent.left;
        anchors.right: parent.right;
        text: file ? file.path : "";
      }
    }

    UI.List {
      title: "Errors";
      visible: root.hasErrors;

      Repeater {
        model: file ? file.errors : null;
        delegate: Item {
          anchors.left: parent.left;
          anchors.right: parent.right;

          height: _errLabel.height + 8;

          UI.Icon {
            id: _errIcon;

            anchors.verticalCenter: parent.verticalCenter;
            rightPadding: 8;

            icon: icons.fa_exclamation_circle;
            color: "#C54632";
          }

          UI.Label {
            id: _errLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: _errIcon.right;
            anchors.right: _errBtn.left;
            anchors.rightMargin: 4;

            text: "[" + modelData.line + ":" + modelData.column + "] " + modelData.message;
          }

          UI.Button {
            id: _errBtn;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            icon: icons.fa_chevron_circle_right;
            frameless: true;

            onClicked: App.document.showSource = true;
          }
        }
      }
    }
  }

  UI.ScrollView {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _outer.bottom;
    anchors.bottom: parent.bottom;

    UI.List {
      visible: file && !root.hasErrors;
      title: "Properties";

      Column {
        id: _controls;

        anchors.left: parent.left;
        anchors.right: parent.right;
      }
    }
  }
}
