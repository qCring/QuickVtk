#pragma once

#include "quickQmlRegister.hpp"

#include <array>
#include <functional>

#include <QObject>

namespace quick::Math {

    class Vector2 : public QObject {
        Q_OBJECT
        Q_PROPERTY(qreal x READ getX WRITE setX NOTIFY xChanged);
        Q_PROPERTY(qreal y READ getY WRITE setY NOTIFY yChanged);
    private:
        using cb_t = std::function<void()>;
        using array_t = std::array<qreal, 2>;
        cb_t m_callback;
        array_t m_values;
        auto notify() -> void;
    public:
        static Qml::Register::UncreatableClass<Vector2> Register;
        Vector2() = delete;
        Vector2(cb_t&&, array_t = {{0,0}});
        auto setX(qreal) -> void;
        auto getX() -> qreal;
        auto setY(qreal) -> void;
        auto getY() -> qreal;
        auto getValues() -> array_t;
    signals:
        void xChanged();
        void yChanged();
    };
}
