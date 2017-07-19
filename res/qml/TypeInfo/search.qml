import QtQuick 2.6

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

        from: Controllers.typeList;
        bind: "filter";

        immediate: true;
        radius: 2;

        onActiveFocusChanged: {
            Controllers.typeList.visible = activeFocus;
        }
    }

    Lib.Label {
        anchors.right: input.right;
        anchors.rightMargin: 4;
        anchors.verticalCenter: parent.verticalCenter;
        text: Controllers.typeList.count + "/" + Controllers.typeList.totalCount;
        font.pointSize: 11;
        font.bold: true;
        visible: input.activeFocus;
    }
}
