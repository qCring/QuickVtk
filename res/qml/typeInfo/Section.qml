import QtQuick 2.6
import "../lib" as Lib

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

        Lib.Icon {
            anchors.verticalCenter: parent.verticalCenter;

            type: types.fa_caret_down;
            pointSize: 12;
        }

        Lib.Label {
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
