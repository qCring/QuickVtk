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
        App.errors.clear();

        try {
            qmlObject = Qt.createQmlObject(App.compiler.source, container, "root");

            if (previousObject) {
                previousObject.destroy();
            }

            previousObject = qmlObject;
            App.compiler.failed = false;
            App.compiler.finished();
        }
        catch (exc) {
            var errors = exc.qmlErrors;

            for (var i = 0; i < errors.length; i++) {
                var error = errors[i];

                App.errors.add(error.lineNumber, error.columnNumber, error.message);
            }

            App.compiler.failed = true;
            App.compiler.finished();
        }
    }

    Connections {
		target: App.compiler;
		onCompile: { root.compile(); }
	}
}
