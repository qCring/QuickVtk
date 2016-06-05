#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Item;
        class Attribute;

        class Group : public QObject {
            Q_OBJECT
            Q_PROPERTY(quick::TypeInfo::Item* item READ getItem CONSTANT);
            Q_PROPERTY(QQmlListProperty<quick::TypeInfo::Attribute> attributes READ getAttributes CONSTANT);
        private:
            Item* m_item;
            QList<Attribute*> m_attributes;
        public:
            static Qml::Register::Type<Group> Register;
            auto getAttributes() -> QQmlListProperty<Attribute>;
            Group() = delete;
            Group(Item*);
            auto getItem() -> Item*;
            auto add(Attribute*) -> void;
        };
    }
}