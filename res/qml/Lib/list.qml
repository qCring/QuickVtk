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

    onModelChanged: {
      positionViewAtEnd();
    }
  }

  Item {
    id: _scroll;

    anchors.right: parent.right;
    anchors.rightMargin: 2;
    anchors.top: parent.top;
    anchors.bottom: parent.bottom;

    //color: "#1B1D23";
    //radius: 4;
    width: 12;

    Item {
      anchors.left: parent.left;
      anchors.right: parent.right;

      height: Math.max(Math.min(_root.height * _root.height / _lv.contentHeight, _root.height), 12);

      Rectangle {
        anchors.fill: parent;
        anchors.margins: 2;

        color: "#3D424E";
        radius: 4;
      }
    }
  }
}
