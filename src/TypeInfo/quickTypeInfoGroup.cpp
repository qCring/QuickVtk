#include "quickTypeInfoGroup.hpp"
#include "quickTypeInfoItem.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Group> Group::Register;

        Group::Group(Item* item) : m_item(item) {

        }

        auto Group::getItem() -> Item* {
            return this->m_item;
        }

        auto Group::add(Attribute* attribute) -> void {
            this->m_attributes.append(attribute);
        }

        auto Group::getAttributes() -> QQmlListProperty<Attribute> {
            return QQmlListProperty<Attribute>(this, this->m_attributes);
        }
    }
}