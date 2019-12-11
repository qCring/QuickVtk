#pragma once

#include "quickQmlRegister.hpp"
#include "quickMenuId.h"

#include <QObject>

namespace quick {
    namespace Menu {
    
        class Item : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
            Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
            Q_PROPERTY(QQmlListProperty<quick::Menu::Item> items READ getItems NOTIFY itemsChanged);
        private:
            QString m_name;
            QString m_icon;
            QString m_data;
            QList<Item*> m_items;
            static Qml::Register::Type<Item> Register;
        public:
            static auto itemsCount(QQmlListProperty<Item>*) -> int;
            static auto itemsAt(QQmlListProperty<Item>*, int) -> Item*;
            const Id id;
        public:
            Item(const QString&, Id id = Id::None);
            Item(const QString&, const QString&, Id id = Id::None);
            auto setName(const QString&) -> void;
            auto getName() -> QString;
            auto setData(const QString&) -> void;
            auto getData() -> QString;
            auto setIcon(const QString&) -> void;
            auto getIcon() -> QString;
            auto getItems() -> QQmlListProperty<Item>;
            auto add(Item*) -> void;
            auto removeItems() -> void;
            auto removeItem(const QString&) -> void;
        signals:
            void nameChanged();
            void iconChanged();
            void itemsChanged();
        };
    }
}
