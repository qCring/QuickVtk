import QtQuick 2.6

import Lib 1.0 as Lib
import Code 1.0 as Code
import TypeInfo 1.0 as TypeInfo

Rectangle {
    id: root;

    color: "#282C34"

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            root.forceActiveFocus();
        }
    }

    Header {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Code.Editor {
        id: editor;

        anchors.left: parent.left;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;
        width: parent.width/2;
    }

    ContainerView {
        anchors.left: editor.right;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;
    }

    TypeInfo.List {
        id: typeList;

        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;
    }

    Notifications {
        anchors.left: parent.left;
        anchors.bottom: footer.top;
        anchors.margins: 4;
    }

    Footer {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
