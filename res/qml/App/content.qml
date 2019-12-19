import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle {
    id: root;

    property var utilsView: undefined;

    clip: true;

    color: "#181A1F"

    Codeview {
      anchors.fill: parent;

      visible: App.document.showSource;
    }

    Item {
      anchors.fill: parent;

      visible: !App.document.showSource;

      Item {
        id: container;

        anchors.fill: parent;
      }

      Item {
        anchors.fill: parent;
        visible: container.children.length < 1;

        Column {
          id: placeholder;

          anchors.centerIn: parent;
          spacing: 8;

          Lib.Icon {
            anchors.horizontalCenter: parent.horizontalCenter;
            icon: icons.fa_folder_open_o;
            font.pointSize: 35;
            color: "#31353B";
          }

          Row {
            anchors.horizontalCenter: parent.horizontalCenter;
            property string color: "#31353B";
            property int textSize: 20;
            spacing: 4;

            Lib.Label {
              anchors.verticalCenter: parent.verticalCenter;
              text: "Open .qml Files from the Menu via File "
              font.pointSize: parent.textSize;
              color: parent.color;
            }

            Lib.Icon {
              anchors.verticalCenter: parent.verticalCenter;
              icon: icons.fa_angle_right;
              color: parent.color;
              font.pointSize: parent.textSize;
            }

            Lib.Label {
              anchors.verticalCenter: parent.verticalCenter;
              text: "Open..."
              font.pointSize: parent.textSize;
              color: parent.color;
            }
          }
        }
      }
    }

    function createComponent() {
      const file = App.document.file;

      if (file == undefined) {
        console.error("unable to create component: App.document.file is undefined");
        return;
      }

      App.document.preRun();

      try {
        if (file.component) {
          file.component.destroy();
        }

        file.component = Qt.createQmlObject(App.document.file.content, container, "root");
      } catch (exc) {
        var errors = exc.qmlErrors;

        if (errors == undefined) {
          console.error(file.title + " - " + exc.message);
          file.addError(0, 0, exc.message);
        } else {
          for (var i = 0; i < errors.length; i++) {
            var error = errors[i];
            console.error(file.title + " [" + error.lineNumber + ":" + error.columnNumber + "] - " + error.message);
            file.addError(error.lineNumber, error.columnNumber, error.message);
          }
        }
      } finally {
        App.document.postRun();
      }
    }

    function destroyComponent(file) {
      if (file) {
        file.component.destroy();
      }
    }

    function selectComponent(file) {
      if (file) {

        for (var i = 0; i < container.children.length; i++) {
          const child = container.children[i];

          if (child != file.component) {
            child.visible = child.enabled = false;
          } else {
            child.visible = child.enabled = true;
          }
        }
      }
    }

    Connections {
        target: App.document;
        onCreateComponent: root.createComponent();
        onDestroyComponent: root.destroyComponent(file);
        onSelectComponent: root.selectComponent(file);
    }
}
