#include "quickMathVector.hpp"

namespace quick {

    namespace Math {

        Qml::Register::VtkClass<Vector> Vector::Register;

        Vector::Vector() : m_values({{0,0,0}}) {
        }

        Vector::Vector(double x, double y, double z) : m_values{{x,y,z,}} {
        }

        auto Vector::notify() -> void {
            for (auto callback : this->m_callbacks) {
                callback->operator()(std::move(*this));
            }
        }

        auto Vector::onChange(std::function<void(Vector&&)>&& callback) -> void {
            this->m_callbacks.append(&callback);
        }

        auto Vector::removeCallback(std::function<void(Vector&&)>&& callback) -> void {
            this->m_callbacks.removeOne(&callback);
        }

        auto Vector::setX(double x) -> void {
            this->m_values[0] = x;
            emit this->xChanged();
            this->notify();
        }

        auto Vector::getX() -> double {
            return this->m_values[0];
        }

        auto Vector::setY(double y) -> void {
            this->m_values[1] = y;
            emit this->yChanged();
            this->notify();
        }

        auto Vector::getY() -> double {
            return this->m_values[1];
        }

        auto Vector::setZ(double z) -> void {
            this->m_values[2] = z;
            emit this->zChanged();
            this->notify();
        }

        auto Vector::getZ() -> double {
            return this->m_values[2];
        }

        auto Vector::getValues() -> std::array<double, 3> {
            return this->m_values;
        }
    }
}