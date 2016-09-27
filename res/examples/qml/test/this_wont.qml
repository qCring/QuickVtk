import QtQuick 2.6
import QtQuick.Controls 1.4

Item {
    anchors.fill: parent;

    Rectangle {
        id: rect;
        width: parent.width;
    }

    Button {
        anchors.centerIn: parent;
        text: "do something stupid";

        onClicked: {
            rect.height = a.height;
        }
    }
}
