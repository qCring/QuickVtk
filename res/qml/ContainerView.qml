import QtQuick 2.5

Item {
    id: root;

    clip: true;


    Item {
        id: container;

        anchors.fill: parent;
    }

    function compile() {
        var qmlObject = undefined;

        try {
            qmlObject = Qt.createQmlObject(App.compiler.source, container, "root");
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
