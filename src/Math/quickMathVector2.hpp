#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QList>
#include <QObject>

namespace quick {

    namespace Math {

        class Vector2 : public QObject {
            Q_OBJECT
            Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged);
            Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged);
        public:
            using cb_t = std::function<void(Vector2&&)>;
        private:
            QList<cb_t*> m_callbacks;
            std::array<double, 2> m_values;
            auto notify() -> void;
        public:
            static Qml::Register::Class<Vector2> Register;
            Vector2();
            Vector2(double, double);
            Vector2(double*);
            auto addCallback(cb_t&&) -> void;
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto getValues() -> std::array<double, 2>;
            auto removeCallback(cb_t&&) -> void;
        signals:
            void xChanged();
            void yChanged();
        };
    }
}