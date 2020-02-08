#pragma once

#include "quickTypeInfoMakeSymbol.hpp"

#include <functional>

#include <QtQml>
#include <QList>
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

namespace quick::Qml {

    auto RegisterTypes() -> void;

    namespace Register {

        struct Initializers {
            static auto GetList() -> QList<std::function<void(void)>>&;
        };

        template <class T>
        struct Controller {
            Controller() {
                auto initializer = [](){
                    qmlRegisterType<T>();
                    T::Create();
                };

                Initializers::GetList().append(initializer);
            }
        };

        template <class T>
        struct Type {
            Type() {
                auto initializer = []() {
                    qmlRegisterType<T>();
                };

                Initializers::GetList().append(initializer);
            }
        };

        template <class T>
        struct AbstractClass {
            AbstractClass(bool isWrapper = false) {
                auto initializer = [isWrapper]() {
                    QMetaObject metaObject = T::staticMetaObject;
                    auto name = QString(metaObject.className());
                    auto prefix = name.section("::", 1, 1);
                    auto className = name.section("::", 2, 2);

                    qmlRegisterUncreatableType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str(), "abstract class \'" + className + "\' can not be instantiated.");

                    for (auto i = 0; i < metaObject.enumeratorCount(); ++i) {
                        TypeInfo::MakeSymbol::Enum(metaObject.enumerator(i));
                    }

                    TypeInfo::MakeSymbol::AbstractClass(metaObject, isWrapper);
                };

                Initializers::GetList().append(initializer);
            }
        };

        template <class T>
        struct UncreatableClass {
            UncreatableClass(bool isWrapper = false) {
                auto initializer = [isWrapper]() {
                    QMetaObject metaObject = T::staticMetaObject;
                    auto name = QString(metaObject.className());
                    auto prefix = name.section("::", 1, 1);
                    auto className = name.section("::", 2, 2);

                    qmlRegisterUncreatableType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str(), "\'" + className + "\' can not be instantiated.");

                    for (auto i = 0; i < metaObject.enumeratorCount(); ++i) {
                        TypeInfo::MakeSymbol::Enum(metaObject.enumerator(i));
                    }

                    TypeInfo::MakeSymbol::Class(metaObject, isWrapper);
                };

                Initializers::GetList().append(initializer);
            }
        };

        template <class T>
        struct Class {
            Class(bool isWrapper = false) {
                auto initializer = [isWrapper]() {
                    QMetaObject metaObject = T::staticMetaObject;
                    auto name = QString(metaObject.className());
                    auto prefix = name.section("::", 1, 1);
                    auto className = name.section("::", 2, 2);

                    qmlRegisterType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str());
                    
                    for (auto i = 0; i < metaObject.enumeratorCount(); ++i) {
                        TypeInfo::MakeSymbol::Enum(metaObject.enumerator(i));
                    }
                    
                    TypeInfo::MakeSymbol::Class(metaObject, isWrapper);
                };

                Initializers::GetList().append(initializer);
            }
        };
    }
}
