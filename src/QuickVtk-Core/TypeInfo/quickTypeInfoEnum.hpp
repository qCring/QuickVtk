#pragma once

#include "quickTypeInfoSymbol.hpp"

#include <QQmlListProperty>

namespace quick::TypeInfo {

    class EnumItem;

    class Enum : public Symbol {
        Q_OBJECT
        Q_PROPERTY(QQmlListProperty<quick::TypeInfo::EnumItem> enumerations READ getEnumItemList CONSTANT);
    private:
        QList<EnumItem*> m_enumItems;
    private:
        friend class Symbol;
        Enum();
    public:
        static Qml::Register::Type<Enum> Register;
        auto add(EnumItem*) -> void;
        auto getEnumItemList() -> QQmlListProperty<EnumItem>;
        auto getAllEnumItems() -> QList<EnumItem*>;
    };
}
