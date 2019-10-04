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
            
            if (type.compare("QString") == 0) {
                type = "string";
            } else if (type.compare("QColor") == 0) {
                type = "color";
            } else if (type.compare("double") == 0) {
                type = "real";
            }

            auto property = new Property();

            property->m_type = type;
            property->m_name = name;
            property->m_sequence = sequence;
            property->m_readonly = !metaProperty.isWritable();

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

        auto Property::isReadonly() -> bool {
            return this->m_readonly;
        }
    }
}
