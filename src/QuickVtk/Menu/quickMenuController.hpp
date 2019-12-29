#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Menu {

        class Item;
    
        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Menu::Item> items READ getItemList CONSTANT);
        private:
            Item* m_fileRecentFiles;
            Item* m_viewToggleConsole;
        private:
            QList<Item*> m_items;
            static Qml::Register::Controller<Controller> Register;
            Controller();
            auto OnFileOpen() -> void;
            auto OnFileOpenRecent(const QString&) -> void;
            auto OnFileClearHistory() -> void;
            auto OnFileClose() -> void;
            auto OnFileQuit() -> void;
            auto OnViewConsole() -> void;
            auto OnViewContext() -> void;
            auto OnViewNextTab() -> void;
            auto OnViewPreviousTab() -> void;
            auto OnHelpAbout() -> void;
            auto OnHelpWebsite() -> void;
        private:
            auto saveRecentFiles() -> void;
        public:
            auto updateViewConsoleMenu(bool) -> void;
            static Controller* instance;
            static auto Init() -> void;
            static auto Create() -> void;
            auto getItemList() -> QQmlListProperty<Item>;
            static auto itemCount(QQmlListProperty<Item>*) -> int;
            static auto itemAt(QQmlListProperty<Item>*, int) -> Item*;
        public slots:
            void select(quick::Menu::Item*);
        };
    }
}
