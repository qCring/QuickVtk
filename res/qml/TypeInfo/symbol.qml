import QtQuick 2.12

import Lib 1.0 as Lib

Rectangle {
    property var symbol;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    height: col.height;
    color: "#ee21252B";

    Column {
        id: col;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.leftMargin: 4;
        topPadding: 4;

        Rectangle {
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.leftMargin: -4;

            height: nameLabel.height + 2;
            color: "#181A1F"

            Row {
                anchors.right: parent.right;
                anchors.rightMargin: 2;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;

                    rightPadding: 4;
                    leftPadding: 4;

                    text: symbol.type;
                    color: symbol.color
                    font.bold: true;
                    font.pointSize: 10;
                }

                Lib.Icon {
                    icon: icons.fa_paste;

                    anchors.verticalCenter: parent.verticalCenter;

                    color: symbol.color;

                    ColorAnimation on color { id: iconColorAnim; running: false; from: "#fff"; to: symbol.color; duration: 1000; }
                }
            }

            Rectangle {
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.bottom: parent.bottom;

                height: 1;

                color: symbol.color
                opacity: 0.3;
            }

            Row {
                id: row;

                anchors.fill: parent;
                anchors.leftMargin: 4;

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;

                    text: symbol.prefix + ".";
                    color: "#6E7582"
                    font.bold: true;
                    font.pointSize: 12;
                }

                Lib.Label {
                    id: nameLabel;

                    anchors.verticalCenter: parent.verticalCenter;

                    text: symbol.name;
                    color: "#fff"
                    font.bold: true;
                    font.pointSize: 12;
                }

                Lib.Label {
                    anchors.verticalCenter: parent.verticalCenter;

                    visible: symbol.base != undefined && symbol.base;
                    text: "  :  " + symbol.base;
                    color: "#6E7582"
                    font.bold: true;
                    font.pointSize: 10;
                }
            }

            MouseArea {
                anchors.fill: parent;
                
                onClicked: function() {
                    context.editor.copyToClipboard(symbol.prefix + "." + symbol.name);
                    iconColorAnim.start();
                }
            }
        }

        Section {
            title: "values"
            model: symbol.enumerations;
            delegate: Enumeration {
                item: model;
                anchors.leftMargin: 12;
            }
        }

        Section {
            title: "properties"
            model: symbol.properties;
            delegate: Property {
                item: model;
                anchors.leftMargin: 12;
            }
        }

        Section {
            title: "methods"
            model: symbol.methods;
            delegate: Method {
                item: model;
                anchors.leftMargin: 12;
            }
        }
    }
}
