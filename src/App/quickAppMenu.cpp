#include "quickAppMenu.hpp"

#include "quickCodeEditor.hpp"

#include <QMenuBar>
#include <iostream>

namespace quick {

    namespace App {

        Menu* Menu::instance = nullptr;

        Menu::Menu() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            instance = this;
        }

        auto Menu::add(QMenu* menu, Type type, const QString& title, QString shortcut) -> void {
            auto item = menu->addAction(title);
            item->setShortcut(shortcut);
            QObject::connect(item, &QAction::triggered, [=](void) { this->onAction(type, title); });
        }

        auto Menu::init() -> void {
            auto menuBar = new QMenuBar(nullptr);

            auto fileMenu = new QMenu(tr("File"), menuBar);
            auto viewMenu = new QMenu(tr("View"), menuBar);
            auto codeMenu = new QMenu(tr("Code"), menuBar);
            auto helpMenu = new QMenu(tr("Help"), menuBar);

            add(fileMenu, FileNewFile, "New File", "Ctrl+N");
            add(fileMenu, FileOpenFile, "Open File", "Ctrl+O");
            add(fileMenu, FileSaveFile, "Save File", "Ctrl+S");

            add(viewMenu, ViewIncreaseFontSize, "Increase Font Size", "Ctrl++");
            add(viewMenu, ViewDecreaseFontSize, "Decrease Font Size", "Ctrl+-");

            add(codeMenu, CodeRun, "Run", "Ctrl+R");
            add(codeMenu, CodeFormat, "Format", "Ctrl+I");

            add(helpMenu, HelpAbout, "About");
            add(helpMenu, HelpDocs, "Documentation");
            add(helpMenu, HelpPrefs, "Preferences...");

            menuBar->addMenu(fileMenu);
            menuBar->addMenu(viewMenu);
            menuBar->addMenu(codeMenu);
            menuBar->addMenu(helpMenu);
        }

        void Menu::onAction(Type type, const QString& title) {
            switch (type) {
                case FileNewFile: Code::Editor::instance->newFile(); break;
                case FileOpenFile: Code::Editor::instance->openFile(); break;
                case FileSaveFile: Code::Editor::instance->saveFile(); break;

                case ViewIncreaseFontSize: Code::Editor::instance->increaseFontSize(); break;
                case ViewDecreaseFontSize: Code::Editor::instance->decreaseFontSize(); break;

                case CodeRun: Code::Editor::instance->run(); break;
                case CodeFormat: Code::Editor::instance->format(); break;

                case HelpAbout: break;
                case HelpDocs: break;
                case HelpPrefs: break;

                default: break;
            }
        }

        auto Menu::Create() -> Menu* {
            auto menu = new Menu();

            menu->init();
            return menu;
        }
    }
}
