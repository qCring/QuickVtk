import QtQuick 2.6
import QtQuick.Controls 1.4

MenuBar {
    property var controller: Controllers.menu;

    Menu {
        title: "File"

        MenuItem {
            text: "New"
            shortcut: "Ctrl+N"
            onTriggered: controller.OnFileNew();
        }

        MenuItem {
            text: "Open..."
            shortcut: "Ctrl+O"
            onTriggered: controller.OnFileOpen();
        }

        MenuSeparator { }

        MenuItem {
            text: "Save"
            shortcut: "Ctrl+S"
            onTriggered: controller.OnFileSave();
        }

        MenuItem {
            text: "Save As..."
            shortcut: "Shift+Ctrl+S"
            onTriggered: controller.OnFileSaveAs();
        }
    }

    Menu {
        title: "Find"

        MenuItem {
            text: "Find..."
            shortcut: "Ctrl+F"
            onTriggered: controller.OnFindFind();
        }
    }

    Menu {
        title: "Code"

        MenuItem {
            text: "Run"
            shortcut: "Ctrl+R"
            onTriggered: controller.OnCodeRun();
        }

        MenuItem {
            text: "Format"
            shortcut: "Ctrl+I"
            onTriggered: controller.OnCodeFormat();
            enabled: false;
        }
    }

    Menu {
        title: "View"

        MenuItem {
            text: "Increase Font Size"
            shortcut: "Ctrl++"
            onTriggered: controller.OnViewIncreaseFontSize();
        }

        MenuItem {
            text: "Decrease Font Size"
            shortcut: "Ctrl+-"
            onTriggered: controller.OnViewDecreaseFontSize();
        }

        MenuItem {
            text: "Reset Font Size"
            onTriggered: controller.OnViewResetFontSize();
        }

        MenuSeparator {}

        MenuItem {
            text: controller.expanded ? "Hide Code Editor" : "Show Code Editor"
            shortcut: "Ctrl+1"
            onTriggered: controller.OnViewToggleEditor();
        }
    }

    Menu {
        title: "Help"

        Menu {
            id: mExamples;
            title: "Examples"

            Instantiator {
                model: controller.examples;
                onObjectAdded: mExamples.insertItem(index, object);
                onObjectRemoved: mExamples.removeItem(object);

                delegate: MenuItem {
                    text: modelData;
                    onTriggered: controller.OnHelpExample(text);
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
            onTriggered: controller.OnHelpVisitOnGitHub();
        }

        MenuItem {
            text: "Send Feedback"
            onTriggered: controller.OnHelpSendFeedback();
        }

        /*
        MenuItem {
            text: "About"
            enabled: false;
        }*/
    }
}
