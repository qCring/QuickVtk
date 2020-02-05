#include "quickTypeInfoClass.hpp"
#include "quickTypeInfoProperty.hpp"
#include "quickTypeInfoMethod.hpp"

namespace quick::TypeInfo {

    Class::Class() {
    }

    auto Class::setAbstract(bool abstract) -> void {
        this->m_abstract = abstract;
    }

    auto Class::isAbstract() -> bool {
        return this->m_abstract;
    }

    auto Class::setBase(const QString& base) -> void {
        this->m_base = base;
    }

    auto Class::getBase() -> QString {
        return this->m_base;
    }

    auto Class::getPropertyList() -> QQmlListProperty<Property> {
        return QQmlListProperty<Property>(this, this->m_properties);
    }

    auto Class::getMethodList() -> QQmlListProperty<Method> {
        return QQmlListProperty<Method>(this, this->m_methods);
    }

    auto Class::addClassProperty(QMetaProperty metaProperty) -> void {
        auto property = Property::Create(metaProperty, Property::Type::ClassProperty);

        if (property) {
            this->m_properties.append(property);
        }
    }

    auto Class::addBaseProperty(QMetaProperty metaProperty) -> void {
        auto property = Property::Create(metaProperty, Property::Type::BaseProperty);
        
        if (property) {
            this->m_properties.append(property);
        }
    }

    auto Class::addClassMethod(QMetaMethod metaMethod) -> void {
        auto method = Method::Create(metaMethod, Method::Type::ClassMethod);

        if (method) {
            this->m_methods.append(method);
        }
    }

    auto Class::addBaseMethod(QMetaMethod metaMethod) -> void {
        auto method = Method::Create(metaMethod, Method::Type::BaseMethod);

        if (method) {
            this->m_methods.append(method);
        }
    }

    auto Class::getAllProperties() -> QList<Property*> {
        return this->m_properties;
    }
    
    auto Class::getAllMethods() -> QList<Method*> {
        return this->m_methods;
    }

    auto Class::addEnumDefinition(const QString& prefix, const QString& name) -> void {
        this->m_enumDefinitions.append(prefix + "." + name);
    }

    auto Class::getAllEnumDefinitions() -> QStringList {
        return this->m_enumDefinitions;
    }
}
