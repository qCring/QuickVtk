#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Attribute : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString type READ getType CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
        private:
            QString m_type;
            QString m_name;
        public:
            static Qml::Register::Type<Attribute> Register;
            Attribute() = delete;
            Attribute(const QString&, const QString&);
            auto getType() -> QString;
            auto getName() -> QString;
        };
    }
}