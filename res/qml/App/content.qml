import QtQuick 2.6
import Lib 1.0 as Lib

Rectangle {
    id: root;

    property var utilsView: undefined;

    clip: true;

    color: "#181A1F"

    Item {
        anchors.fill: parent;

        Item {
          id: container;

          anchors.fill: parent;
          anchors.bottomMargin: 40;
        }

        Rectangle {
          anchors.left: parent.left;
          anchors.right: parent.right;
          anchors.bottom: parent.bottom;

          height: 40;

          Row {
            anchors.fill: parent;

            Repeater {
              model: container.children;
              Text {
                text: index;
              }
            }
          }
        }
    }

    Rectangle {
        color: "#000"
        border.color: "#6E7582";
        width: 30;
        height: 22;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.margins: 4;
        radius: 4;
        opacity: ma.containsMouse ? 1 : 0.3;

        visible: Controllers.expanded;

        Lib.Icon {
            anchors.centerIn: parent;

            icon: icons.fa_navicon;
            color: ma.containsMouse ? "#fff" : "#9DA5B4";
        }

        MouseArea {
            id: ma;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: Controllers.expanded = false;
        }
    }

    function createComponent() {
      const file = Controllers.document.file;
      console.log("component.createComponent: file: " + file);

      if (file == undefined) {
        console.error("unable to create component: Controllers.document.file is undefined");
        return;
      }

      Controllers.document.preRun();

      try {
        if (file.component) {
          file.component.destroy();
        }

        file.component = Qt.createQmlObject(Controllers.document.file.content, container, "root");
      } catch (exc) {
        var errors = exc.qmlErrors;

        console.log("errors: " + errors);

        if (errors == undefined) {
          console.log("msg: " + exc.message);
          file.addError(0, 0, exc.message);
        } else {
          for (var i = 0; i < errors.length; i++) {
              var error = errors[i];

              file.addError(error.lineNumber, error.columnNumber, error.message);
          }
        }
      } finally {
        Controllers.document.postRun();
      }
    }

    function destroyComponent(file) {
      if (file) {
        console.log("component.destroyComponent: " + file.component);
        file.component.destroy();
      }
    }

    function selectComponent(file) {
      if (file) {
        console.log("content: selectComponent: " + file.component);

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
        target: Controllers.document;
        onCreateComponent: root.createComponent();
        onDestroyComponent: root.destroyComponent(file);
        onSelectComponent: root.selectComponent(file);
    }
}
