#pragma once

#include "quickTypeInfoSymbol.hpp"

#include <QQmlListProperty>

namespace quick {

    namespace TypeInfo {
        
        class Class : public Symbol {
            Q_OBJECT
            Q_PROPERTY(bool abstract READ isAbstract CONSTANT);
            Q_PROPERTY(QQmlListProperty<class quick::TypeInfo::Property> properties READ getPropertyList CONSTANT);
            Q_PROPERTY(QQmlListProperty<class quick::TypeInfo::Method> methods READ getMethodList CONSTANT);
            Q_PROPERTY(QString base READ getBase CONSTANT);
        private:
            friend class Symbol;
            bool m_abstract = false;
            QString m_base;
            QStringList m_enumDefinitions;
            QList<class Property*> m_properties;
            QList<class Method*> m_methods;
        private:
            Class();
        public:
            static Qml::Register::Type<Class> Register;
            auto getPropertyList() -> QQmlListProperty<class Property>;
            auto getMethodList() -> QQmlListProperty<class Method>;
            auto setAbstract(bool) -> void;
            auto isAbstract() -> bool;
            auto setBase(const QString&) -> void;
            auto getBase() -> QString;
            auto addEnumDefinition(const QString& prefix, const QString& name) -> void;
            auto addBaseProperty(QMetaProperty) -> void;
            auto addClassProperty(QMetaProperty) -> void;
            auto addMethod(QMetaMethod) -> void;
            auto getAllProperties() -> QList<class Property*>;
            auto getAllMethods() -> QList<class Method*>;
            auto getAllEnumDefinitions() -> QStringList;
        };
    }
}
