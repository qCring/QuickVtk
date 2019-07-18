#include "quickTypeInfoProperty.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Property> Property::Register;

        auto Property::Create(QMetaProperty metaProperty) -> Property* {
            auto name = QString(metaProperty.name());

            if (name == "objectName") {
                return nullptr;
            }

            auto sequence = false;
            auto type = QString(metaProperty.typeName()).remove("*").remove("quick::").replace("::", ".");

            if (type.contains("List")) {
                sequence = true;
                if (auto bracketIndex = type.lastIndexOf("<")) {
                    type.remove(0, bracketIndex + 1);
                    type = type.remove("<").remove(">");
                } else if (type.contains("string")) {
                    type = "string";
                }
            }

            if (type.startsWith("Q") && type.length() > 2) {
                QChar character = type.at(1);
                type = type.remove(0, 2);
                type.push_front(character.toLower());
            }

            auto property = new Property();

            property->m_type = type;
            property->m_name = name;
            property->m_sequence = sequence;
            property->m_readable = metaProperty.isReadable();
            property->m_writable = metaProperty.isWritable();

            return property;
        }

        auto Property::getType() -> QString {
            return this->m_type;
        }

        auto Property::getName() -> QString {
            return this->m_name;
        }

        auto Property::isSequence() -> bool {
            return this->m_sequence;
        }

        auto Property::isWritable() -> bool {
            return this->m_writable;
        }

        auto Property::isReadable() -> bool {
            return this->m_readable;
        }
    }
}
