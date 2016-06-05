import QtQuick 2.6

import "./../lib" as Lib

Rectangle {

    visible: App.typeList.visible;

    width: visible ? 260 : 0;
    clip: true;
    color: "#21252B"

    Item {
        id: search;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        height: 30;

        Lib.Icon {
            id: icon;

            anchors.left: parent.left;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.leftMargin: 4;

            type: types.fa_search;
            color: input.activeFocus ? "#fff" : "#6E7582"
        }

        Lib.TextInput {
            id: input;

            anchors.left: icon.right;
            anchors.right: parent.right;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;
            anchors.margins: 4;

            from: App.typeList;
            bind: "filter";

            immediate: true;
            radius: 2;
        }

        Rectangle {
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;

            height: 1;
            color: "#181A1F"
        }
    }

    ListView {
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: search.bottom;
        anchors.bottom: parent.bottom;

        boundsBehavior: Flickable.StopAtBounds;
        clip: true;

        model: App.typeList;
        delegate: Symbol {
            symbol: model.symbol;
        }
    }

    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        width: 1;

        color: "#181A1F"
    }
}
