#pragma once

#include <QtQml>

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
        }
    }
}