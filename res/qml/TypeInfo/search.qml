import QtQuick 2.12

import UI 1.0 as UI

Item {
  id: root;

  height: input.height;
  width: 280;

  UI.TextInput {
    id: input;

    anchors.left: _ic.right;
    anchors.right: _clear.left;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    bottomPadding: 8;
    topPadding: 8;

    from: App.typeList;
    bind: "filter";

    immediate: true;

    onActiveFocusChanged: {
      App.typeList.visible = activeFocus;
    }
  }

  UI.Icon {
    id: _ic;

    anchors.left: parent.left;
    anchors.verticalCenter: parent.verticalCenter;

    icon: icons.fa_search;
    color: input.activeFocus ? "#fff" : "#6E7582"
    rightPadding: 8;
    leftPadding: 8;
  }

  UI.Button {
    id: _clear;

    anchors.right: parent.right;
    anchors.rightMargin: 4;
    anchors.verticalCenter: parent.verticalCenter;

    frameless: true;
    icon: icons.fa_times_circle;
    visible: input.text.length > 0;

    onClicked: input.text = "";
  }
}
