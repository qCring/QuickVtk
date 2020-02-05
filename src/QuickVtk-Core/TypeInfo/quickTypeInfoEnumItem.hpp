#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::TypeInfo {

    class EnumItem : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName CONSTANT);
        Q_PROPERTY(int value READ getValue CONSTANT);
    private:
        QString m_name;
        int m_value;
    public:
        static Qml::Register::Type<EnumItem> Register;
        EnumItem() = delete;
        EnumItem(const QString&, const int);
        auto getName() -> QString;
        auto getValue() -> int;
    };
}
