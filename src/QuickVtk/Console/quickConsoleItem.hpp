#pragma once

#include "quickQmlRegister.hpp"

namespace quick {
    namespace Console {

        class Item : public QObject {
            Q_OBJECT
        public:
            enum Type {
                Info,
                Debug,
                Warning,
                Error
            };
        private:
            Q_ENUM(Type);
            Q_PROPERTY(QString description READ getDescription CONSTANT);
            Q_PROPERTY(Type type READ getType CONSTANT);
            Q_PROPERTY(QString time READ getTime CONSTANT);
            Q_PROPERTY(QString label READ getLabel CONSTANT);
        private:
            Type m_type;
            QString m_description;
            QString m_label;
            QString m_time;
            static Qml::Register::Type<Item> Register;
        private:
            auto typeToString(Type) -> QString;
        public:
            Item(const QString&, Type);
            auto getDescription() -> QString;
            auto getLabel() -> QString;
            auto getType() -> Type;
            auto getTime() -> QString;
        };
    }
}
