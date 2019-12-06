#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class MenuItem;
    
        class Menu : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::App::MenuItem> items READ getItemList CONSTANT);
        private:
            static Menu* instance;
            QList<MenuItem*> m_items;
            static Qml::Register::Type<Menu> Register;
            MenuItem* m_recentFiles;
            auto init() -> void;
            Menu();
            auto OnFileOpen() -> void;
            auto OnFileOpenRecent(const QString&) -> void;
            auto OnFileQuit() -> void;
            auto OnHelpAbout() -> void;
            auto OnHelpWebsite() -> void;
        public:
            static auto GetInstance() -> Menu*;
            auto getItemList() -> QQmlListProperty<MenuItem>;
            static auto itemCount(QQmlListProperty<MenuItem>*) -> int;
            static auto itemAt(QQmlListProperty<MenuItem>*, int) -> MenuItem*;
        public slots:
            void select(quick::App::MenuItem*);
        };
    }
}
