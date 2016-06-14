#pragma once

#include "quickTypeInfoSymbol.hpp"

#include <QQmlListProperty>

namespace quick {

    namespace TypeInfo {

        class Property;
        class Method;
        
        class Class : public Symbol {
            Q_OBJECT
            Q_PROPERTY(bool abstract READ isAbstract CONSTANT);
            Q_PROPERTY(QQmlListProperty<quick::TypeInfo::Property> properties READ getPropertyList CONSTANT);
            Q_PROPERTY(QQmlListProperty<quick::TypeInfo::Method> methods READ getMethodList CONSTANT);
        private:
            friend class Symbol;
            bool m_abstract = false;
            QList<Property*> m_properties;
            QList<Method*> m_methods;
        private:
            Class();
        public:
            static Qml::Register::Type<Class> Register;
            auto getPropertyList() -> QQmlListProperty<Property>;
            auto getMethodList() -> QQmlListProperty<Method>;
            auto setAbstract(bool) -> void;
            auto isAbstract() -> bool;
            auto addProperty(QMetaProperty) -> void;
            auto addMethod(QMetaMethod) -> void;
        };
    }
}