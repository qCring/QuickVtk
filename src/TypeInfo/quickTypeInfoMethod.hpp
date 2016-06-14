#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace TypeInfo {

        class Method : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString returnType READ getReturnType CONSTANT);
            Q_PROPERTY(QString paramTypes READ getParamTypes CONSTANT);
            Q_PROPERTY(QString name READ getName CONSTANT);
            Q_PROPERTY(bool sequence READ isSequence CONSTANT);
        private:
            bool m_sequence = false;
            QString m_returnType;
            QString m_paramTypes;
            QString m_name;
        private:
            Method() = default;
        public:
            static Qml::Register::Type<Method> Register;
            static auto Create(QMetaMethod) -> Method*;
            auto getReturnType() -> QString;
            auto getParamTypes() -> QString;
            auto getName() -> QString;
            auto isSequence() -> bool;
        };
    }
}