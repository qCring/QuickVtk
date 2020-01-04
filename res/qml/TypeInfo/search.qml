import QtQuick 2.12

import Lib 1.0 as Lib

Item {
    id: root;

    height: 30;
    width: 280;

    Lib.Icon {
        id: icon;

        anchors.left: parent.left;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.leftMargin: 4;

        icon: icons.fa_search;
        color: input.activeFocus ? "#fff" : "#6E7582"
    }

    Lib.TextInput {
        id: input;

        anchors.left: icon.right;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.margins: 4;

        topPadding: 4;
        bottomPadding: 4;

        from: App.typeList;
        bind: "filter";

        immediate: true;
        radius: 2;

        onActiveFocusChanged: {
            App.typeList.visible = activeFocus;
        }
    }

    Lib.Label {
        anchors.right: input.right;
        anchors.rightMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        text: App.typeList.count + "/" + App.typeList.totalCount;
        font.pointSize: 11;
    }
}
