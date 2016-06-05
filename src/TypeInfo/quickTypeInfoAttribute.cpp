#include "quickTypeInfoAttribute.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Attribute> Attribute::Register;
        
        Attribute::Attribute(const QString& type, const QString& name) : m_type(type), m_name(name) {

        }

        auto Attribute::getType() -> QString {
            return this->m_type;
        }

        auto Attribute::getName() -> QString {
            return this->m_name;
        }
    }
}
