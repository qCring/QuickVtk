#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace App {
    
        class MenuItem : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
            Q_PROPERTY(QQmlListProperty<quick::App::MenuItem> items READ getItems NOTIFY itemsChanged);
        private:
            QString m_name;
            QList<MenuItem*> m_items;
            static Qml::Register::Type<MenuItem> Register;
        public:
            static auto itemsCount(QQmlListProperty<MenuItem>*) -> int;
            static auto itemsAt(QQmlListProperty<MenuItem>*, int) -> MenuItem*;
        public:
            MenuItem(const QString&);
            auto setName(const QString&) -> void;
            auto getName() -> QString;
            auto getItems() -> QQmlListProperty<MenuItem>;
            auto add(MenuItem*) -> void;
        signals:
            void nameChanged();
            void itemsChanged();            
        };
    }
}
