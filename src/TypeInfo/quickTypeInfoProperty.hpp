#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Property : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool wirteable READ isWriteable CONSTANT);
            Q_PROPERTY(bool readable READ isReadable CONSTANT);
            Q_PROPERTY(QString type READ getType CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
        private:
            bool m_writeable = false;
            bool m_readable = false;
            QString m_type;
            QString m_name;
        private:
            Property() = default;
        public:
            static Qml::Register::Type<Property> Register;
            static auto Create(QMetaProperty) -> Property*;
            auto isWriteable() -> bool;
            auto isReadable() -> bool;
            auto getType() -> QString;
            auto getName() -> QString;
        };
    }
}