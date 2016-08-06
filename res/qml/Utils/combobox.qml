import QtQuick 2.6
import QtQuick.Controls 1.4

import Lib 1.0 as Lib

Item {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    height: combobox.height;

    property alias model: combobox.model;
    property alias label: label.text;
    property bool checked;

    signal indexChanged(var index);

    Lib.Label {
        id: label;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        width: 100;

        text: root.bind;
    }

    ComboBox {
        id: combobox;

        anchors.left: label.right;
        anchors.right: parent.right;
        anchors.leftMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;

        onCurrentIndexChanged: root.indexChanged(currentIndex);
    }
}
