import QtQuick 2.6

import App 1.0 as App
import Lib 1.0 as Lib

Rectangle {
    id: root;

    color: "#282C34";

    property string tabTitle: "Log [" + App.logger.entries.length + "]";

    ListView {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: footer.top;

        model: App.logger.entries;
        delegate: Lib.Label {
            anchors.left: parent.left;
            anchors.right: parent.right;
            text: modelData;
        }
    }

    Rectangle {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        height: footerCol.height;

        color: "#282C34";

        Column {
            id: footerCol;

            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;

            Rectangle {
                anchors.left: parent.left;
                anchors.right: parent.right;
                height: 1;

                color: "#21252B";
            }

            Lib.Button {
                anchors.right: parent.right;
                anchors.rightMargin: 4;
                icon.type: icon.types.fa_trash_o;
                label.text: "Clear"

                onClicked: App.logger.clear();
            }
        }
    }
}
