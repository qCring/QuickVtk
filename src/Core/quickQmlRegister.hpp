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

            template <class T>
            struct VtkAbstractClass {
                VtkAbstractClass() {
                    auto initializer = []() {
                        QMetaObject metaObject = T::staticMetaObject;
                        auto name = QString(metaObject.className());
                        auto groupName = name.section("::", 1, 1);
                        auto className = name.section("::", 2, 2);

                        qmlRegisterUncreatableType<T>(groupName.toStdString().c_str(), 1, 0, className.toStdString().c_str(), "abstract class \'" + className + "\' can not be instantiated.");
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };


            template <class T>
            struct VtkClass {
                VtkClass() {
                    auto initializer = []() {
                        QMetaObject metaObject = T::staticMetaObject;
                        auto name = QString(metaObject.className());
                        auto groupName = name.section("::", 1, 1);
                        auto className = name.section("::", 2, 2);

                        qmlRegisterType<T>(groupName.toStdString().c_str(), 1, 0, className.toStdString().c_str());
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