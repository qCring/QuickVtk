#pragma once

#include <functional>

#include <QtQml>
#include <QList>
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

namespace quick {

    namespace Qml {

        namespace Register {

            auto Init() -> void;
#ifdef _MSC_VER
            struct Queue {
                static auto GetList()->QList<std::function<void(void)>>&;
            };
#endif

            template <class T>
            struct Controller {
                Controller() {
                    auto initializer = [](){
                        qmlRegisterType<T>();
                        T::Create();
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };

            template <class T>
            struct Type {
                Type() {
                    auto initializer = []() {
                        qmlRegisterType<T>();
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };

            namespace Symbol {

                namespace Make {
                    auto Enum(QMetaEnum) -> void;
                    auto Class(QMetaObject, bool isWrapper) -> void;
                    auto AbstractClass(QMetaObject, bool isWrapper) -> void;
                }

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
                                Make::Enum(metaObject.enumerator(i));
                            }

                            Make::AbstractClass(metaObject, isWrapper);
                        };
#ifdef _MSC_VER
                        Queue::GetList().append(initializer);
#else
                        initializer();
#endif
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
                                Make::Enum(metaObject.enumerator(i));
                            }

                            Make::Class(metaObject, isWrapper);
                        };
#ifdef _MSC_VER
                        Queue::GetList().append(initializer);
#else
                        initializer();
#endif
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
                                Make::Enum(metaObject.enumerator(i));
                            }
                            
                            Make::Class(metaObject, isWrapper);
                        };
#ifdef _MSC_VER
                        Queue::GetList().append(initializer);
#else
                        initializer();
#endif
                    }
                };
            }
        }
    }
}
