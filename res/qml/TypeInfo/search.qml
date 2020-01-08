import QtQuick 2.12

import Lib 1.0 as Lib

Item {
    id: root;

    height: input.height;
    width: 280;

    Lib.TextInput {
        id: input;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        bottomPadding: 8;
        topPadding: 8;
        leftPadding: _ic.width;

        from: App.typeList;
        bind: "filter";

        immediate: true;

        onActiveFocusChanged: {
            App.typeList.visible = activeFocus;
        }

        Lib.Icon {
          id: _ic;

          anchors.left: parent.left;
          anchors.verticalCenter: parent.verticalCenter;
          icon: icons.fa_search;
          color: input.activeFocus ? "#fff" : "#6E7582"
          rightPadding: 8;
          leftPadding: 8;
        }
    }

    Lib.Label {
        anchors.right: input.right;
        anchors.rightMargin: 8;
        anchors.verticalCenter: parent.verticalCenter;
        text: App.typeList.count + "/" + App.typeList.totalCount;
        font.pointSize: 11;
    }
}
