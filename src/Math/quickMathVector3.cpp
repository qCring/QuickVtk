#include "quickMathVector3.hpp"

namespace quick {

    namespace Math {

        Qml::Register::Class<Vector3> Vector3::Register;

        Vector3::Vector3() : m_values({{0,0,0}}) {
        }

        Vector3::Vector3(double x, double y, double z) : m_values{{x,y,z}} {
        }

        auto Vector3::notify() -> void {
            for (auto callback : this->m_callbacks) {
                callback->operator()(std::move(*this));
            }
        }

        auto Vector3::addCallback(cb_t&& callback) -> void {
            if (this->m_callbacks.contains(&callback)) {
                return;
            }

            this->m_callbacks.append(&callback);
        }

        auto Vector3::removeCallback(cb_t&& callback) -> void {
            this->m_callbacks.removeOne(&callback);
        }

        auto Vector3::setX(double x) -> void {
            this->m_values[0] = x;
            emit this->xChanged();
            this->notify();
        }

        auto Vector3::getX() -> double {
            return this->m_values[0];
        }

        auto Vector3::setY(double y) -> void {
            this->m_values[1] = y;
            emit this->yChanged();
            this->notify();
        }

        auto Vector3::getY() -> double {
            return this->m_values[1];
        }

        auto Vector3::setZ(double z) -> void {
            this->m_values[2] = z;
            emit this->zChanged();
            this->notify();
        }

        auto Vector3::getZ() -> double {
            return this->m_values[2];
        }

        auto Vector3::getValues() -> std::array<double, 3> {
            return this->m_values;
        }
    }
}