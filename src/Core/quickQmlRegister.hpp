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
#ifdef _MSC_VER
                    Queue::GetList().append([]() {
                        qmlRegisterType<T>();
                        T::Create();
                    });
#else
                    qmlRegisterType<T>();
                    T::Create();
#endif
                }
            };

            template <class T>
            struct Type {
                Type() {
                    qmlRegisterType<T>();
                }
            };

            template <class T>
            struct VtkClass {
                VtkClass() {
#ifdef _MSC_VER
                    Queue::GetList().append([]() {
                        QMetaObject metaObject = T::staticMetaObject;
                        auto name = QString(metaObject.className());
                        auto groupName = name.section("::", 1, 1);
                        auto className = name.section("::", 2, 2);

                        qmlRegisterType<T>(groupName.toStdString().c_str(), 1, 0, className.toStdString().c_str());
                    });
#else
                    QMetaObject metaObject = T::staticMetaObject;
                    auto name = QString(metaObject.className());
                    auto groupName = name.section("::", 1, 1);
                    auto className = name.section("::", 2, 2);
                    
                    qmlRegisterType<T>(groupName.toStdString().c_str(), 1, 0, className.toStdString().c_str());
#endif
                }
            };
        }
    }
}