import QtQuick 2.6

import Lib 1.0 as Lib

Column {
    property var symbol;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;
    spacing: 2;

    Rectangle {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: nameLabel.height + 4;

        color: "#282C34"

        Lib.Label {
            id: prefixLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;

            text: symbol.prefix + ".";
            color: "#6E7582"
            font.bold: true;
            font.pointSize: 12;
        }

        Lib.Label {
            id: nameLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: prefixLabel.right;
            anchors.right: typeLabel.left;
            anchors.rightMargin: 4;

            text: symbol.name;
            color: "#fff"
            font.bold: true;
            font.pointSize: 12;
        }

        Lib.TagLabel {
            id: typeLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;
            height: nameLabel.height;

            label.text: symbol.type;
            color: "#21252B"
            border.color: "#6E7582";
            label.color: symbol.color;
            label.font.weight: Font.Bold;
            label.font.pointSize: 10;
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
