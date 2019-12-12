import QtQuick 2.12
import QtQuick.Controls 2.12

import Lib 1.0 as Lib

Item {
    id: root;

    anchors.left: parent.left;
    anchors.right: parent.right;
    height: combobox.height;

    property alias model: combobox.model;
    property alias label: label.text;
    property alias currentIndex: combobox.currentIndex;

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
