import QtQuick 2.6
import QtQuick.Window 2.2

import Lib 1.0 as Lib
import Code 1.0 as Code
import TypeInfo 1.0 as TypeInfo

Window {
    id: root;

    color: "#282C34"

    Menu {
    }

    Header {
        id: header;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
    }

    Lib.SplitView {
        id: splitView;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;

        leftItem: Code.Editor {
            anchors.fill: parent;
        }

        rightItem: Lib.TabView {
            anchors.fill: parent;

            Preview {
                anchors.fill: parent;
            }

            LogView {
                anchors.fill: parent;
            }
        }
    }

    TypeInfo.List {
        id: typeList;

        anchors.right: parent.right;
        anchors.top: header.bottom;
        anchors.bottom: footer.top;
    }

    Footer {
        id: footer;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
    }

    
}
