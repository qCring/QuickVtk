import QtQuick 2.5

Item {
    id: root;

    property var previousObject: undefined;

    clip: true;

    Item {
        id: container;

        anchors.fill: parent;
    }

    function compile() {
        var qmlObject = undefined;

        try {
            qmlObject = Qt.createQmlObject(App.compiler.source, container, "root");

            if (previousObject) {
                previousObject.destroy();
            }

            previousObject = qmlObject;
            App.compiler.finished();
        }
        catch (exc) {
            console.log (exc);
        }
    }

    Connections {
		target: App.compiler;
		onCompile: { root.compile(); }
	}
}
