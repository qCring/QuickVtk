import QtQuick 2.6

import Lib 1.0 as Lib

Rectangle {
    id: root;

    property string tabTitle: "Preview"

    property var previousObject: undefined;

    clip: true;

    color: "#181A1F"

    Item {
        id: container;

        anchors.fill: parent;
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

        visible: App.expanded;

        Lib.Icon {
            anchors.centerIn: parent;

            type: types.fa_navicon;
            color: ma.containsMouse ? "#fff" : "#9DA5B4";
        }

        MouseArea {
            id: ma;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: App.expanded = false;
        }
    }

    function compile() {
        var qmlObject = undefined;
        App.editor.errors.clear();

        try {
            qmlObject = Qt.createQmlObject(App.editor.getText(), container, "root");

            if (previousObject) {
                previousObject.destroy();
            }

            previousObject = qmlObject;
        }
        catch (exc) {
            var errors = exc.qmlErrors;

            for (var i = 0; i < errors.length; i++) {
                var error = errors[i];

                App.editor.errors.add(error.lineNumber, error.columnNumber, error.message);
            }

            App.editor.errors.update();
        }
    }

    Connections {
		target: App.editor;
		onCompile: root.compile();
	}
}
