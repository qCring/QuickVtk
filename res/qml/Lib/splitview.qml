import QtQuick 2.6

import Lib 1.0 as Lib

Item {
    id: root;

    property alias leftItem: leftContainer.children;
    property alias rightItem: rightContainer.children;

    clip: true;

    property int minRight: 100;
    property int minLeft: 100;
    property color handleBorder: ma.containsMouse || ma.pressed ? "#3C424F" : leftContainer.minimized || rightContainer.minimized ? "#282C34" : "#21252B";

    function setSplitLocation(val) {
        anchor.x = val;

        lockAnchor();
    }

    function collapseLeft() {
        anchor.anchors.right        = undefined;
        anchor.anchors.left         = root.left;
        anchor.anchors.rightMargin  = 0;

        anchor.anchors.leftMargin = 0;
        leftContainer.minimized = true;
        rightContainer.minimized = false;
    }

    function collapseRight() {
        anchor.anchors.left         = undefined;
        anchor.anchors.right        = root.right;
        anchor.anchors.leftMargin   = 0;

        anchor.anchors.rightMargin = 0;
        leftContainer.minimized = false;
        rightContainer.minimized = true;
    }

    function expandLeft(margin) {
        anchor.anchors.right        = undefined;
        anchor.anchors.left         = root.left;
        anchor.anchors.rightMargin  = 0;

        anchor.anchors.leftMargin = Qt.binding (function(){ return Math.min (margin, root.width); });
        leftContainer.minimized = false;
        rightContainer.minimized = false;
    }

    function expandRight(margin) {
        anchor.anchors.left         = undefined;
        anchor.anchors.right        = root.right;
        anchor.anchors.leftMargin   = 0;

        anchor.anchors.rightMargin = Qt.binding (function() { return Math.min (margin, root.width); });
        leftContainer.minimized = false;
        rightContainer.minimized = false;
    }

    function lockAnchor() {
        if (anchor.x > width / 2) {
            var margin = root.width - anchor.x;

            if (margin < minRight) {
                collapseRight();
            } else {
                expandRight(margin);
            }
        } else {
            var margin = anchor.x;

            if (margin < minLeft) {
                collapseLeft();
            } else {
                expandLeft(margin);
            }
        }
    }

    function unlockAnchor() {
        anchor.anchors.left     = undefined;
        anchor.anchors.right    = undefined;
    }

    Item {
        id: leftContainer;

        property real sizeFac: 1 - Math.min(1, width / 16)
        property bool minimized: false;

        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: anchor.left;
    }

    Item {
        id: rightContainer;

        property real sizeFac: 1 - Math.min(1, width / 16);
        property bool minimized: false;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        anchors.left: anchor.right;
    }

    Rectangle {
        id: anchor;

        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        x: parent.width/2;

        width: 1;

        color: root.handleBorder;
    }

    Rectangle {
        id: leftHandle;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: leftContainer.sizeFac * width / 2 - width;

        width: (leftIcon.width + 6) * 2;
        height: leftIcon.height * 2;
        radius: 3;

        color: "#181A1F";
        border.color: root.handleBorder;

        Lib.Icon {
            id: leftIcon;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.right: parent.right;
            anchors.rightMargin: 4;
            type: types.fa_chevron_right;
            pointSize: 16;
            color: Qt.lighter(root.handleBorder);
        }

        MouseArea {
            anchors.fill: parent;
            enabled: leftContainer.minimized;

            onClicked: {
                unlockAnchor();
                expandLeft (root.minLeft * 2);
            }
        }
    }

    Rectangle {
        id: rightHandle;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: rightContainer.sizeFac * width / 2 - width;

        width: (rightIcon.width + 6) * 2;
        height: rightIcon.height * 2;
        radius: 3;

        color: "#181A1F";
        border.color: root.handleBorder;

        Lib.Icon {
            id: rightIcon;

            anchors.verticalCenter: parent.verticalCenter;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            type: types.fa_chevron_left;
            pointSize: 16;
            color: Qt.lighter(root.handleBorder);
        }

        MouseArea {
            anchors.fill: parent;
            enabled: rightContainer.minimized;

            onClicked: {
                unlockAnchor();
                expandRight (root.minRight * 2);
            }
        }
    }

    MouseArea {
        id: ma;

        anchors.fill: anchor;

        anchors.leftMargin: rightContainer.minimized ? - rightHandle.width / 2 : - 4;
        anchors.rightMargin: leftContainer.minimized ? - leftHandle.width / 2 : - 4;

        hoverEnabled: true;

        drag.target: anchor;
        drag.smoothed: false;
        drag.minimumX: 0;
        drag.maximumX: root.width;
        drag.axis: Drag.XAxis;

        onPressed: root.unlockAnchor();
        onReleased: root.lockAnchor();
    }
}
