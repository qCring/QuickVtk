#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace App {
    
        class MenuItem : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
            Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
            Q_PROPERTY(QQmlListProperty<quick::App::MenuItem> items READ getItems NOTIFY itemsChanged);
        public:
            enum class Action {
                None,
                File_Open,
                File_Open_Recent,
                File_Quit,
                Edit_Settings,
                View_Console,
                View_Context,
                Help_About,
                Help_Website
            };
        private:
            QString m_name;
            QString m_icon;
            QString m_data;
            QList<MenuItem*> m_items;
            static Qml::Register::Type<MenuItem> Register;
        public:
            static auto itemsCount(QQmlListProperty<MenuItem>*) -> int;
            static auto itemsAt(QQmlListProperty<MenuItem>*, int) -> MenuItem*;
            const Action action;
        public:
            MenuItem(const QString&, Action action = Action::None);
            MenuItem(const QString&, const QString&, Action action = Action::None);
            auto setName(const QString&) -> void;
            auto getName() -> QString;
            auto setData(const QString&) -> void;
            auto getData() -> QString;
            auto setIcon(const QString&) -> void;
            auto getIcon() -> QString;
            auto getItems() -> QQmlListProperty<MenuItem>;
            auto add(MenuItem*) -> void;
            auto removeItems() -> void;
        signals:
            void nameChanged();
            void iconChanged();
            void itemsChanged();            
        };
    }
}
