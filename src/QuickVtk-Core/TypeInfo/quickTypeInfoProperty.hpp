#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Property : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool sequence READ isSequence CONSTANT);
            Q_PROPERTY(bool readonly READ isReadonly CONSTANT);
            Q_PROPERTY(bool inherited READ isInherited CONSTANT);
            Q_PROPERTY(QString type READ getType CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
        public:
            enum class Type {
                BaseProperty,
                ClassProperty
            };
        private:
            bool m_readonly = false;
            bool m_sequence = false;
            bool m_inherited = false;
            QString m_type;
            QString m_name;
        private:
            Property() = default;
        public:
            static Qml::Register::Type<Property> Register;
            static auto Create(QMetaProperty, Type) -> Property*;
            auto isSequence() -> bool;
            auto isReadonly() -> bool;
            auto isInherited() -> bool;
            auto getType() -> QString;
            auto getName() -> QString;
        };
    }
}
