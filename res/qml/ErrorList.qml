import QtQuick 2.6

import "./lib" as Lib

Column {
    spacing: 2;

    width: 100;

    Repeater {
        model: App.errors;
        delegate: Rectangle {
            height: 20;
            width: row.width;
            color: "#111"
            radius: 2;

            Row {
                id: row;

                anchors.top: parent.top;
                anchors.bottom: parent.bottom;

                spacing: 4;

                Lib.TagLabel {
                    anchors.top: parent.top;
                    anchors.bottom: parent.bottom;
                    color: "#ff0000"
                    label.text: "Error";
                }

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;
                    text: model.line + ":" + model.column + ":";
                    font.pixelSize: 11;
                }

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;
                    text: model.message + "  ";
                    font.pixelSize: 11;
                    color: "#fff"
                }
            }
        }
    }
}
