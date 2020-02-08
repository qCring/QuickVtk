#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::Menu {

    class Item;

    class Controller : public QObject {
        Q_OBJECT
        Q_PROPERTY(QQmlListProperty<quick::Menu::Item> items READ getItemList CONSTANT);
    private:
        Item* m_fileRecentFiles;
        Item* m_viewToggleConsole;
        Item* m_viewToggleInspector;
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
        auto OnViewInspector() -> void;
        auto OnViewNextTab() -> void;
        auto OnViewPreviousTab() -> void;
    private:
        auto saveRecentFiles() -> void;
    public:
        auto updateViewConsoleMenu(bool) -> void;
        auto updateViewInspectorMenu(bool) -> void;
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
