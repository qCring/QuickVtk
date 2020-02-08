#include "quickTypeInfoProperty.hpp"
#include "quickTypeInfoSymbol.hpp"

namespace quick::TypeInfo {

    Qml::Register::Type<Property> Property::Register;

    auto Property::Create(QMetaProperty metaProperty, Type type) -> Property* {
        auto name = QString(metaProperty.name());

        if (name == "objectName") {
            return nullptr;
        }

        auto sequence = false;
        auto typeName = Symbol::PrettifyTypeName(QString(metaProperty.typeName()));

        if (typeName.contains("List")) {
            sequence = true;
        }
        
        auto property = new Property();

        property->m_type = typeName;
        property->m_name = name;
        property->m_sequence = sequence;
        property->m_readonly = !metaProperty.isWritable();
        property->m_inherited = type == Type::BaseProperty;

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

    auto Property::isInherited() -> bool {
        return this->m_inherited;
    }
}
