import QtQuick 2.12
import UI 1.0 as UI

Item {
  id: root;

  property alias controls: _controls;
  property var file: App.document.file;
  property var hasErrors: file ? file.errors.length > 0 : false;

  Column {
    id: _header;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: parent.top;

    anchors.topMargin: 8;
    anchors.leftMargin: 8;
    anchors.rightMargin: 16;

    spacing: 8;

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;

      height: _title.height;

      UI.Label {
        id: _title;

        anchors.left: parent.left;
        anchors.right: _indicator.left;
        anchors.verticalCenter: parent.verticalCenter;

        font.pointSize: 15;
        color: "#fff";
        text: "File";
      }

      UI.Icon {
        id: _indicator;

        anchors.right: parent.right;
        anchors.verticalCenter: parent.verticalCenter;

        icon: root.hasErrors ? icons.fa_times_circle : icons.fa_check;
        color: root.hasErrors ? "#C54632" : "#2BA468";
        visible: root.file;
      }
    }

    UI.Label {
      anchors.left: parent.left;
      anchors.right: parent.right;

      text: root.file ? file.title : "No file selected";
    }

    UI.Label {
      anchors.left: parent.left;
      anchors.right: parent.right;

      text: root.file ? file.path : "";
    }
  }

  Rectangle {
    id: _separator;

    anchors.top: _header.bottom;
    anchors.topMargin: 8;
    anchors.left: parent.left;
    anchors.right: parent.right;

    height: 1;
    color: "#181A1F";
    visible: _sv.scrolled; 
  }

  UI.ScrollView {
    id: _sv;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.top: _separator.bottom;
    anchors.bottom: parent.bottom;

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

    UI.List {
      visible: _controls.children.length > 0;
      title: "Properties";

      bottomPadding: 64;

      Column {
        id: _controls;

        anchors.left: parent.left;
        anchors.right: parent.right;
      }
    }
  }
}
