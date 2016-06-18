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
        public:
            using cb_t = std::function<void(Vector3&&)>;
        private:
            QList<cb_t*> m_callbacks;
            std::array<double, 3> m_values;
            auto notify() -> void;
        public:
            static Qml::Register::Class<Vector3> Register;
            Vector3();
            Vector3(double, double, double);
            Vector3(double*);
            auto addCallback(cb_t&&) -> void;
            auto setX(double) -> void;
            auto getX() -> double;
            auto setY(double) -> void;
            auto getY() -> double;
            auto setZ(double) -> void;
            auto getZ() -> double;
            auto getValues() -> std::array<double, 3>;
            auto removeCallback(cb_t&&) -> void;
        signals:
            void xChanged();
            void yChanged();
            void zChanged();
        };
    }
}