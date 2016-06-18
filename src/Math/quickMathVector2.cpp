#include "quickMathVector2.hpp"

namespace quick {

    namespace Math {

        Qml::Register::Class<Vector2> Vector2::Register;

        Vector2::Vector2() : m_values({{0,0}}) {
        }

        Vector2::Vector2(double x, double y) : m_values{{x,y}} {
        }

        auto Vector2::notify() -> void {
            for (auto callback : this->m_callbacks) {
                callback->operator()(std::move(*this));
            }
        }

        auto Vector2::addCallback(cb_t&& callback) -> void {
            if (this->m_callbacks.contains(&callback)) {
                return;
            }

            this->m_callbacks.append(&callback);
        }

        auto Vector2::removeCallback(cb_t&& callback) -> void {
            this->m_callbacks.removeOne(&callback);
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

        auto Vector2::getValues() -> std::array<double, 2> {
            return this->m_values;
        }
    }
}