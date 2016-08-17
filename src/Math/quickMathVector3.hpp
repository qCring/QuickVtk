#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QList>
#include <QObject>

namespace quick {

    namespace Math {

        class Vector3 : public QObject {
            Q_OBJECT
            Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
            Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
            Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged);
        private:
            using cb_t = std::function<void()>;
            using array_t = std::array<double, 3>;
            cb_t m_callback;
            array_t m_values;
            auto notify() -> void;
        public:
            static Qml::Register::UncreatableClass<Vector3> Register;
            Vector3() = delete;
            Vector3(cb_t&&, array_t = {{0,0,0}});
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto setZ(double) -> void;
            auto getZ() -> double;
            auto getValues() -> std::array<double, 3>;
        signals:
            void xChanged();
            void yChanged();
            void zChanged();
        };
    }
}