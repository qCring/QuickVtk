#pragma once

#include <QMetaObject>
#include <QMetaEnum>

namespace quick::TypeInfo::MakeSymbol {

    auto Enum(QMetaEnum metaEnum) -> void;
    auto Class(QMetaObject metaObject, bool) -> void;
    auto AbstractClass(QMetaObject metaObject, bool) -> void;
}
