import QtQuick 2.12

Item {
  id: _root;

  property alias model: _lv.model;
  property alias delegate: _lv.delegate;
  property alias spacing: _lv.spacing;

  ListView {
    id: _lv;

    boundsBehavior: Flickable.StopAtBounds;
    boundsMovement: Flickable.StopAtBounds;

    anchors.left: parent.left;
    anchors.right: _scroll.left;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;
    
    clip: true;

    property int lastY: 0;

    onContentYChanged: {
      if (!_ma.pressed) {
        if (_lv.moving) {
          lastY = contentY;
        }

        _handle.y = contentY / _handle.scrollRatio;
      }
    }

    onMovingChanged: {
      if (!moving) {
        lastY = contentY;
        _handle.released();
      }
    }

    onModelChanged: {
      if (_ma.pressed) {
        contentY = lastY;
        return;
      }

      if (_handle.sticky) {
        positionViewAtEnd();
        return;
      }

      if (model == undefined || model.length == 0) {
        lastY = contentY = 0;
        return;
      }

      contentY = lastY;
    }
  }

  Item {
    id: _scroll;

    anchors.right: parent.right;
    anchors.rightMargin: 2;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    width: 12;

    Item {
      id: _handle;

      anchors.left: parent.left;
      anchors.right: parent.right;

      height: Math.max(Math.min(_root.height * _root.height / _lv.contentHeight, _root.height), 16);
      property real scrollRatio: (_lv.contentHeight - _root.height) / (_root.height - height);
      property bool sticky: false;

      Rectangle {
        anchors.fill: parent;
        anchors.margins: 2;

        color: "#3D424E";
        radius: 4;
      }

      onYChanged: {
        if (_ma.pressed) {
          _lv.contentY = _lv.lastY = y * scrollRatio;
        }
      }

      function released() { // make handle sticky if near bottom
        if (_handle.y > _root.height - _handle.height - 5) { // 5px tolerance
          _handle.sticky = true;
        } else {
          _handle.sticky = false;
        }
      }

      MouseArea {
        id: _ma;

        anchors.fill: parent;

        drag.target: parent;
        drag.axis: Drag.YAxis;
        drag.minimumY: 0;
        drag.maximumY: _root.height - _handle.height;

        onReleased: {
          _handle.released();
        }
      }
    }
  }
}
