import QtQuick 2.12

import Lib 1.0 as Lib

Item {
    id: root;

    property var utilsView: undefined;

    Tabs {
      id: tabs;

      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.top: parent.top;
    }

    Content {
      utilsView: root.utilsView;

      anchors.top: tabs.bottom;
      anchors.left: parent.left;
      anchors.right: parent.right;
      anchors.bottom: parent.bottom;
    }
}
