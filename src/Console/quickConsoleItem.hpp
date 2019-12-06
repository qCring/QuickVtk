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
            Q_PROPERTY(QString message READ getMessage CONSTANT);
            Q_PROPERTY(Type type READ getType CONSTANT);
            Q_PROPERTY(QString time READ getTime CONSTANT);
        private:
            Type m_type;
            QString m_message;
            QString m_time;
            static Qml::Register::Type<Item> Register;
        public:
            Item(const QString&, Type);
            auto getMessage() -> QString;
            auto getType() -> Type;
            auto getTime() -> QString;
        };
    }
}
