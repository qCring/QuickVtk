import QtQuick 2.5

import "./lib" as Lib

Rectangle {
    color: "#282C34"

    Header {
        id: header;
        
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    ContainerView {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;
    }

    Footer {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }
}
