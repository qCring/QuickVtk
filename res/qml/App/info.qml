import QtQuick 2.12
import UI 1.0 as UI

Item {
  id: root;

  property alias controls: _controls;
  property var file: App.document.file;
  property var hasErrors: file ? file.errors.length > 0 : false;

  UI.ScrollView {
    id: _sv;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;

      height: _content.height;

      Column {
        id: _content;

        anchors.left: parent.left;
        anchors.right: parent.right;

        topPadding: 8;
        bottomPadding: 8;
        spacing: 8;

        Item {
          anchors.left: parent.left;
          anchors.right: parent.right;
          height: _title.height;

          Item {
            anchors.left: parent.left;
            anchors.right: parent.right;

            height: _title.height;

            UI.Label {
              id: _title;

              anchors.left: parent.left;
              anchors.verticalCenter: parent.verticalCenter;

              font.pointSize: 15;
              color: "#fff";
              text: "File";
            }

            UI.Label {
              anchors.right: parent.right;
              anchors.verticalCenter: parent.verticalCenter;
              anchors.rightMargin: 2;

              text: file ? file.title : "";
            }
          }
        }

        UI.Label {
          anchors.left: parent.left;
          anchors.right: parent.right;
          text: file ? file.path : "No file selected"
          wrapMode: Text.Wrap;
          topPadding: 8;
        }
      }
    }

    UI.List {
      title: "Errors";
      visible: root.hasErrors;

      bottomPadding: 64;

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

    Item {
      visible: _controls.children.length > 0;
      anchors.left: parent.left;
      anchors.right: parent.right;
      height: _controls.height;

      Column {
        id: _controls;

        anchors.left: parent.left;
        anchors.right: parent.right;

        bottomPadding: 64;
      }
    }
  }
}
