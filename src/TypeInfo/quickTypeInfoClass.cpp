#include "quickTypeInfoClass.hpp"
#include "quickTypeInfoProperty.hpp"

namespace quick {

    namespace TypeInfo {

        Class::Class() {
        }

        auto Class::setAbstract(bool abstract) -> void {
            this->m_abstract = abstract;
        }

        auto Class::isAbstract() -> bool {
            return this->m_abstract;
        }

        auto Class::getPropertyList() -> QQmlListProperty<Property> {
            return QQmlListProperty<Property>(this, this->m_properties);
        }

        auto Class::addProperty(QMetaProperty metaProperty) -> void {
            auto property = Property::Create(metaProperty);

            if (property) {
                this->m_properties.append(property);
            }
        }
    }
}
