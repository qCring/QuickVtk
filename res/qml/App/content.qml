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
      }

      Item {
        anchors.fill: parent;
        visible: container.children.length < 1;

        Column {
          anchors.centerIn: parent;

          Lib.Icon {
            anchors.horizontalCenter: parent.horizontalCenter;
            icon: icons.fa_folder_open_o;
            font.pointSize: 80;
            color: "#21252B";
          }

          Lib.Label {
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "Open File"
            font.pointSize: 25;
            font.bold: true;
            color: "#21252B";
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

        if (errors == undefined) {
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
        target: Controllers.document;
        onCreateComponent: root.createComponent();
        onDestroyComponent: root.destroyComponent(file);
        onSelectComponent: root.selectComponent(file);
    }
}
