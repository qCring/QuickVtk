import QtQuick 2.12

import UI 1.0 as UI

Item {
  id: root;

  default property alias content: _content.children;

  Flickable {
    id: _flick;

    anchors.left: parent.left;
    anchors.right: _scroll.left;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    flickableDirection: Flickable.VerticalFlick;
    boundsBehavior: Flickable.StopAtBounds;
    boundsMovement: Flickable.StopAtBounds;

    contentHeight: _content.height;
    clip: true;

    Column {
      id: _content;

      anchors.left: parent.left;
      anchors.right: parent.right;
    }

    onContentYChanged: {
      if (!_ma.pressed) {
        _handle.y = contentY / _handle.scrollRatio;
      }
    }
  }

  Item {
    id: _scroll;

    anchors.right: parent.right;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    property bool showHandle: _flick.contentHeight > root.height;
    visible: showHandle;
    width: showHandle ? 12 : 0;

    Item {
      id: _handle;

      anchors.left: parent.left;
      anchors.right: parent.right;

      height: Math.max(Math.min(root.height * root.height / _flick.contentHeight, root.height), 16);
      property real scrollRatio: (_flick.contentHeight - root.height) / (root.height - height);

      Rectangle {
        anchors.fill: parent;
        anchors.margins: 2;

        color: "#3D424E";
        radius: 4;
      }

      onYChanged: {
        if (_ma.pressed) {
          _flick.contentY = y * scrollRatio;
        }
      }

      MouseArea {
        id: _ma;

        anchors.fill: parent;

        drag.target: parent;
        drag.axis: Drag.YAxis;
        drag.minimumY: 0;
        drag.maximumY: root.height - _handle.height;
      }
    }
  }
}
