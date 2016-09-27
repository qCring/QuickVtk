import QtQuick 2.6

import Lib 1.0 as Lib

Item {
    id: root;

    default property alias content: container.children;

    property var visibleItem: undefined;
    property int selectedIndex: -1;

    Item {
        id: container;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: footer.top;
    }

    onSelectedIndexChanged: {
        if (visibleItem) {
            visibleItem.visible = false;
        }

        container.children[selectedIndex].visible = true;
        root.visibleItem = container.children[selectedIndex];
    }

    Rectangle {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        color: "#21252B";

        height: 20;
        clip: true;

        Row {
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

            Repeater {
                model: container.children;

                delegate: Rectangle {
                    id: panel;

                    width: label.width + 24;
                    anchors.top: parent.top;
                    anchors.topMargin: -radius;
                    anchors.bottom: parent.bottom;
                    anchors.bottomMargin: 1;
                    radius: 4;

                    color: index == root.selectedIndex ? "#282C34" : "#18191E";

                    Lib.Label {
                        id: label;

                        anchors.centerIn: parent;
                        anchors.verticalCenterOffset: panel.radius/2;
                        enabled: index == root.selectedIndex;

                        text: container.children[index].tabTitle;
                    }

                    MouseArea {
                        anchors.fill: parent;
                        anchors.topMargin: -panel.radius;
                        onClicked: {
                            root.selectedIndex = index;
                        }
                    }
                }
            }
        }

        Rectangle {
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: parent.top;
            height: 1;
            color: "#21252B"
        }
    }

    Component.onCompleted: {
        for (var i = 0; i < container.children.length; i++) {
            container.children[i].visible = false;
        }

        root.selectedIndex = 0;
    }
}
