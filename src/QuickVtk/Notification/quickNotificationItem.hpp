#pragma once

#include "quickQmlRegister.hpp"

namespace quick {
    namespace Notification {

        class Item : public QObject {
            Q_OBJECT
        public:
            enum Type {
                Info,
                Warning,
                Error
            };
        private:
            Q_ENUM(Type);
            Q_PROPERTY(QString title READ getTitle CONSTANT);
            Q_PROPERTY(QString description READ getDescription CONSTANT);
            Q_PROPERTY(Type type READ getType CONSTANT);
        private:
            Type m_type;
            QString m_title;
            QString m_description;
            static Qml::Register::Type<Item> Register;
        public:
            Item(const QString&, const QString&, Type);
            auto getDescription() -> QString;
            auto getTitle() -> QString;
            auto getType() -> Type;
        };
    }
}
