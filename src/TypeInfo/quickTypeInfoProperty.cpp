#include "quickTypeInfoProperty.hpp"

#include <iostream>

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Property> Property::Register;

        auto Property::Create(QMetaProperty metaProperty) -> Property* {
            auto name = QString(metaProperty.name());

            if (name == "objectName") {
                return nullptr;
            }

            auto type = QString(metaProperty.typeName()).remove("*").remove("quick::").replace("::", ".");

            if (type.contains("List")) {
                if (auto bracketIndex = type.lastIndexOf("<")) {
                    type.remove(0, bracketIndex);
                    type.push_front("list ");
                } else if (type.contains("string")) {
                    type = "list <string>";
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
            property->m_readable = metaProperty.isReadable();
            property->m_writeable = metaProperty.isWritable();

            return property;
        }

        auto Property::getType() -> QString {
            return this->m_type;
        }

        auto Property::getName() -> QString {
            return this->m_name;
        }

        auto Property::isWriteable() -> bool {
            return this->m_writeable;
        }

        auto Property::isReadable() -> bool {
            return this->m_readable;
        }
    }
}
