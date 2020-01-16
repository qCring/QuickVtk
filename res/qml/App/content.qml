import QtQuick 2.12

import UI 1.0 as UI

Rectangle {
    id: root;

    property var controls: undefined;

    clip: true;

    color: "#282C34"

    Editor {
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

          UI.Icon {
            anchors.horizontalCenter: parent.horizontalCenter;
            icon: icons.fa_folder_open_o;
            font.pointSize: 35;
            color: "#4C5363";
          }

          Row {
            anchors.horizontalCenter: parent.horizontalCenter;
            property string color: "#4C5363";
            property int textSize: 20;
            spacing: 4;

            UI.Label {
              anchors.verticalCenter: parent.verticalCenter;
              text: "Open .qml Files from the Menu via File "
              font.pointSize: parent.textSize;
              color: parent.color;
            }

            UI.Icon {
              anchors.verticalCenter: parent.verticalCenter;
              icon: icons.fa_angle_right;
              color: parent.color;
              font.pointSize: parent.textSize;
            }

            UI.Label {
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
        file.component = null;
        
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
