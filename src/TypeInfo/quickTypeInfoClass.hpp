#pragma once

#include "quickTypeInfoSymbol.hpp"

#include <QQmlListProperty>

namespace quick {

    namespace TypeInfo {

        class Property;
        
        class Class : public Symbol {
            Q_OBJECT
            Q_PROPERTY(bool abstract READ isAbstract CONSTANT);
            Q_PROPERTY(QQmlListProperty<quick::TypeInfo::Property> properties READ getPropertyList CONSTANT);
        private:
            friend class Symbol;
            bool m_abstract = false;
            QList<Property*> m_properties;
        private:
            Class();
        public:
            static Qml::Register::Type<Class> Register;
            auto getPropertyList() -> QQmlListProperty<Property>;
            auto setAbstract(bool) -> void;
            auto isAbstract() -> bool;
            auto addProperty(QMetaProperty) -> void;
        };
    }
}