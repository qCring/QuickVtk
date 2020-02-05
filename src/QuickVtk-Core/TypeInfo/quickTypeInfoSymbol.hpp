#pragma once

#include "quickQmlRegister.hpp"

#include <QMetaObject>
#include <QObject>
#include <QColor>

namespace quick::TypeInfo {

    class Symbol : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName CONSTANT);
        Q_PROPERTY(QString prefix READ getPrefix CONSTANT);
        Q_PROPERTY(int type READ getType CONSTANT);
    private:
        struct Get {
            static auto ClassName(QMetaObject) -> QString;
            static auto ClassPrefix(QMetaObject) -> QString;
            static auto EnumName(QMetaEnum) -> QString;
            static auto EnumPrefix(QMetaEnum) -> QString;
            static auto BaseString(QMetaObject) -> QString;
        };
    private:
        QString m_name;
        QString m_prefix;
        int m_type; // 0 = abstract, 1 = class, 2 = enum
        bool m_isWrapper = false;
    private:
        static auto GetEnums() -> QStringList&;
        static auto PrettifyType(QString) -> QString;
    public:
        static Qml::Register::Type<Symbol> Register;
        static auto MakeEnum(QMetaEnum) -> void;
        static auto MakeClass(QMetaObject, bool isWrapper) -> void;
        static auto MakeAbstractClass(QMetaObject, bool isWrapper) -> void;
        static auto PrettifyTypeName(QString) -> QString;
        auto operator < (const Symbol&) -> const bool;
        auto getName() -> QString;
        auto getPrefix() -> QString;
        auto isWrapper() -> bool;
        auto getType() -> int;
        auto matches(const QString&) -> bool;
    };
}
