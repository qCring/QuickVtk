#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QObject>

namespace quick::Math {

    class Vector3 : public QObject {
        Q_OBJECT
        Q_PROPERTY(qreal x READ getX WRITE setX NOTIFY xChanged);
        Q_PROPERTY(qreal y READ getY WRITE setY NOTIFY yChanged);
        Q_PROPERTY(qreal z READ getZ WRITE setZ NOTIFY zChanged);
    private:
        using cb_t = std::function<void()>;
        using array_t = std::array<qreal, 3>;
        cb_t m_callback;
        array_t m_values;
        auto notify() -> void;
    public:
        static Qml::Register::UncreatableClass<Vector3> Register;
        Vector3() = delete;
        Vector3(cb_t&&, array_t = {{0,0,0}});
        Vector3(array_t);
        auto setX(qreal) -> void;
        auto getX() -> qreal;
        auto setY(qreal) -> void;
        auto getY() -> qreal;
        auto setZ(qreal) -> void;
        auto getZ() -> qreal;
        auto setFromVtkArray(double*) -> void;
        auto getValues() -> array_t;
    signals:
        void xChanged();
        void yChanged();
        void zChanged();
    };
}
