#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Group : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString name READ getName CONSTANT);
        private:
            QString m_name;
        public:
            static Qml::Register::Type<Group> Register;
            auto setName(const QString&) -> void;
            auto getName() -> QString;
        };
    }
}