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

        if (file == undefined) {
          console.error("unable to create component: Controllers.document.file is undefined");
          return;
        }

        try {
          file.root = Qt.createQmlObject(Controllers.document.file.content, container, "root");
        } catch (exc) {
          var errors = exc.qmlErrors;

          for (var i = 0; i < errors.length; i++) {
              var error = errors[i];

              file.addError(error.lineNumber, error.columnNumber, error.message);
          }
        }
    }

    function destroyComponent(file) {
      if (file != undefined) {
        console.log("destroy file.root: " + file.root);
        file.root.destroy();
      }
    }

    function selectComponent(file) {
      console.log("select: " + file + " root: " + file.root);

      if (file != undefined && container.children.length > 0) {
        for (var i = 0; i < container.children.length; i++) {
          const child = container.children[i];

          console.log(" it: " + i + " child: " + child);

          child.visible = false;
          child.enabled = false;
        }

        if (file.root != undefined) {
          file.root.visible = true;
          file.root.enabled = true;  
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
