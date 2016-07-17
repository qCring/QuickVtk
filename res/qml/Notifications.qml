import QtQuick 2.6

import "./lib" as Lib

Column {
    spacing: 2;

    width: 100;

    Repeater {
        model: App.notifications;
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
                    color: model.isError ? "#ff0000" : model.isWarning ? "#cc6600" : "#666"
                    label.text: model.isError ? "Error" : model.isWarning ? "Warning" : "Info";
                }

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;
                    text: model.line + ":" + model.column + ":";
                    font.pointSize: 11;
                    visible: model.isError;
                }

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;
                    text: model.message + "  ";
                    font.pointSize: 11;
                    color: "#fff"
                }
            }
        }
    }
}
