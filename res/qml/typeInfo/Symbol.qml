import QtQuick 2.6

import "./../lib" as Lib

Column {
    property var symbol;

    anchors.left: parent ? parent.left : undefined;
    anchors.right: parent ? parent.right : undefined;

    Item {
        anchors.left: parent.left;
        anchors.right: parent.right;

        height: 24;

        Lib.TagLabel {
            id: typeTag;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            width: height;

            label.text: symbol.type[0];
            color: "#00000000"
            border.color: symbol.color
            label.color: symbol.color;
            label.font.weight: Font.Bold;
            label.font.pointSize: 10;
        }

        Lib.Label {
            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: typeTag.right;
            anchors.leftMargin:4;
            anchors.right: prefixLabel.left;

            text: symbol.name;
            color: symbol.color;
            font.bold: true;
            font.pointSize: 12;
        }

        Lib.Label {
            id: prefixLabel;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;

            text: symbol.prefix;
            color: symbol.color;
            font.weight: Font.Bold;
            font.pointSize: 10;
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
