import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import Lib 1.0 as Lib
import Code 1.0 as Code
import TypeInfo 1.0 as TypeInfo

ApplicationWindow {
    id: root;

    color: "#282C34"

    menuBar: MenuBar {

        Menu {
            title: "File"

            MenuItem {
                text: "New"
                shortcut: "Ctrl+N"
                onTriggered: Controllers.menu.OnFileNew();
            }

            MenuItem {
                text: "Open..."
                shortcut: "Ctrl+O"
                onTriggered: Controllers.menu.OnFileOpen();
            }

            MenuSeparator { }

            MenuItem {
                text: "Save"
                shortcut: "Ctrl+S"
                onTriggered: Controllers.menu.OnFileSave();
            }

            MenuItem {
                text: "Save As..."
                shortcut: "Shift+Ctrl+S"
                onTriggered: Controllers.menu.OnFileSaveAs();
            }
        }

        Menu {
            title: "Find"

            MenuItem {
                text: "Find..."
                shortcut: "Ctrl+F"
                onTriggered: Controllers.menu.OnFindFind();
            }
        }

        Menu {
            title: "Code"

            MenuItem {
                text: "Run"
                shortcut: "Ctrl+R"
                onTriggered: Controllers.menu.OnCodeRun();
            }

            MenuItem {
                text: "Format"
                shortcut: "Ctrl+I"
                onTriggered: Controllers.menu.OnCodeFormat();
                enabled: false;
            }
        }

        Menu {
            title: "View"

            MenuItem {
                text: "Increase Font Size"
                shortcut: "Ctrl++"
                onTriggered: Controllers.menu.OnViewIncreaseFontSize();
            }

            MenuItem {
                text: "Decrease Font Size"
                shortcut: "Ctrl+-"
                onTriggered: Controllers.menu.OnViewDecreaseFontSize();
            }

            MenuItem {
                text: "Reset Font Size"
                onTriggered: Controllers.menu.OnViewResetFontSize();
            }

            MenuSeparator {}

            MenuItem {
                text: Controllers.menu.expanded ? "Hide Code Editor" : "Show Code Editor"
                shortcut: "Ctrl+1"
                onTriggered: Controllers.menu.OnViewToggleEditor();
            }
        }

        Menu {
            title: "Help"

            Menu {
                id: mExamples;
                title: "Examples"

                Instantiator {
                    model: Controllers.menu.examples;
                    onObjectAdded: mExamples.insertItem(index, object);
                    onObjectRemoved: mExamples.removeItem(object);

                    delegate: MenuItem {
                        text: modelData;
                        onTriggered: Controllers.menu.OnHelpExample(text);
                    }
                }
            }

            MenuSeparator {}

        /*
        MenuItem {
            text: "Documentation"
            onTriggered: controller.OnHelpDocumentation();
            enabled: false;
            }*/

            MenuItem {
                text: "Visit on GitHub"
                onTriggered: Controllers.menu.OnHelpVisitOnGitHub();
            }

            MenuItem {
                text: "Send Feedback"
                onTriggered: Controllers.menu.OnHelpSendFeedback();
            }

        /*
        MenuItem {
            text: "About"
            enabled: false;
            }*/
        }
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
