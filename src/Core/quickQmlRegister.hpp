#pragma once

#include <QtQml>
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

namespace quick {
    namespace Qml {
        namespace Register {
            template <class T>
            struct Controller {
                Controller() {
                    qmlRegisterType<T>();
                    T::Create();
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
                    QMetaObject metaObject = T::template staticMetaObject;

                    auto name = QString(metaObject.className());
                    auto groupName = name.section("::", 1, 1);
                    auto className = name.section("::", 2, 2);

                    qmlRegisterType<T>(groupName.toStdString().c_str(), 1, 0, className.toStdString().c_str());
                }
            };
        }
    }
}