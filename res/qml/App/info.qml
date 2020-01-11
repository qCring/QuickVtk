import QtQuick 2.12
import UI 1.0 as UI

Item {
  id: root;

  property alias controls: _controls;
  property var file: App.document.file;
  property var hasErrors: file ? file.errors.length > 0 : false;
  anchors.topMargin: 16;

  Column {
    id: _info;

    anchors.left: parent.left;
    anchors.right: parent.right;

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;
      height: _label.height;

      UI.Label {
        id: _label;

        anchors.left: parent.left;
        anchors.right: _indicator.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.rightMargin: 4;

        text: file ? file.title : "No file selected"
        color: file ? "#fff" : "#6E7582"
      }

      UI.Icon {
        id: _indicator;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        visible: file;
        icon: root.hasErrors ? icons.fa_exclamation_circle : icons.fa_check;
        color: root.hasErrors ? "#C54632" : "#2BA468";
      }
    }

    UI.Label {
      anchors.left: parent.left;
      anchors.right: parent.right;

      text: file ? file.path : ""
      font.pointSize: 11;
    }
  }

  UI.Area {
    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _info.bottom;
    anchors.topMargin: 16;
    anchors.bottom: parent.bottom;

    visible: root.file;

    Item {
      id: _header;

      anchors.left: parent.left;
      anchors.right: parent.right;

      height: 30;

      UI.Label {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 8;

        font.pointSize: 14;
        font.bold: true;
        color: "#fff";
        text: root.hasErrors ? "Errors" : "Properties";
      }

      Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        height: 1;
        color: "#21252B"
      }
    }

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: _header.bottom;
      anchors.bottom: parent.bottom;
      anchors.topMargin: 8;

      Item {
        id: _controls;

        anchors.fill: parent;
      }

      Item { // Errors Container
        anchors.fill: parent;

        visible: root.hasErrors;

        Column {
          anchors.left: parent.left;
          anchors.right: parent.right;
          anchors.top: parent.top;
          anchors.leftMargin: 8;
          anchors.rightMargin: 8;

          Repeater {
            model: file? file.errors : 0;
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
    }
  }
}
