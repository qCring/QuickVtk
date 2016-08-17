#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QObject>

namespace quick {

    namespace Math {

        class Vector2 : public QObject {
            Q_OBJECT
            Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
            Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
        private:
            using cb_t = std::function<void()>;
            using array_t = std::array<double, 2>;
            cb_t m_callback;
            array_t m_values;
            auto notify() -> void;
        public:
            static Qml::Register::UncreatableClass<Vector2> Register;
            Vector2() = delete;
            Vector2(cb_t&&, array_t = {{0,0}});
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto getValues() -> array_t;
        signals:
            void xChanged();
            void yChanged();
        };
    }
}