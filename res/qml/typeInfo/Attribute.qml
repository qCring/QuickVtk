import QtQuick 2.6

import "./../lib" as Lib

Lib.Label {
    property var attribute;

    anchors.left: parent.left;
    anchors.right: parent.right;
    topPadding: 2;
    bottomPadding: 2;

    font.pixelSize: 10;
    text: attribute.type + ": " + attribute.name;
}
