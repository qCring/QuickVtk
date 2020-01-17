#include "quickMathVector2.hpp"

namespace quick {
    namespace Math {

        Qml::Register::UncreatableClass<Vector2> Vector2::Register;

        Vector2::Vector2(cb_t&& callback, array_t values) : m_callback(callback), m_values(values) {
        }

        auto Vector2::notify() -> void {
            this->m_callback.operator()();
        }

        auto Vector2::setX(double x) -> void {
            this->m_values[0] = x;
            emit this->xChanged();
            this->notify();
        }

        auto Vector2::getX() -> double {
            return this->m_values[0];
        }

        auto Vector2::setY(double y) -> void {
            this->m_values[1] = y;
            emit this->yChanged();
            this->notify();
        }

        auto Vector2::getY() -> double {
            return this->m_values[1];
        }

        auto Vector2::getValues() -> array_t {
            return this->m_values;
        }
    }
}
