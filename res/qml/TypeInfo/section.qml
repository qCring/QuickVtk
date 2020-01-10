import QtQuick 2.12

import UI 1.0 as UI

Column {
    property alias model: repeater.model;
    property alias delegate: repeater.delegate;
    property alias title: label.text;

    anchors.left: parent.left;
    anchors.right: parent.right;
    anchors.leftMargin: 8;

    visible: model != undefined && model.length > 0;

    Row {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 20;
        spacing: 4;

        property alias text: label.text;

        UI.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            icon: icons.fa_caret_down;
            iconSize: 12;
        }

        UI.Label {
            id: label;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.margins: 4;

            font.pointSize: 12;
            font.weight: Font.Medium;

            color: "#9DA5B4"
        }
    }

    Repeater {
        id: repeater;
    }
}
