#include "quickTypeInfoEnumItem.hpp"

namespace quick::TypeInfo {

    Qml::Register::Type<EnumItem> EnumItem::Register;

    EnumItem::EnumItem(const QString& name, const int value) : m_name(name), m_value(value) {
    }

    auto EnumItem::getName() -> QString {
        return this->m_name;
    }

    auto EnumItem::getValue() -> int {
        return this->m_value;
    }
}
