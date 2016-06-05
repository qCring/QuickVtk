import QtQuick 2.6

import "./../lib" as Lib

Lib.Label {
    property var item;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 24;

    topPadding: 2;
    bottomPadding: 2;

    font.pixelSize: 10;
    text: item.name + ": " + item.type;
}
