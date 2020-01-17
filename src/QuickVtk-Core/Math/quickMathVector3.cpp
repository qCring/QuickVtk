#include "quickMathVector3.hpp"

namespace quick {
    namespace Math {

        Qml::Register::UncreatableClass<Vector3> Vector3::Register;

        Vector3::Vector3(cb_t&& cb, array_t values) : m_callback(cb), m_values(values) {
        }

        auto Vector3::notify() -> void {
            this->m_callback.operator()();
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

        auto Vector3::getValues() -> array_t {
            return this->m_values;
        }
    }
}
