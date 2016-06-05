import QtQuick 2.6

import "./../lib" as Lib

Column {
    property var group;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 24;

    Repeater {
        model: group.attributes;
        delegate: Attribute {
            attribute: model;
        }
    }
}
