#include "quickMathVector3.hpp"

namespace quick::Math {

    Qml::Register::UncreatableClass<Vector3> Vector3::Register;

    Vector3::Vector3(array_t values) : m_values(values) {
    }
    
    Vector3::Vector3(cb_t&& cb, array_t values) : m_callback(cb), m_values(values) {
    }

    auto Vector3::notify() -> void {
        if (this->m_callback != nullptr) {
            this->m_callback.operator()();
        }
    }
    
    auto Vector3::setFromVtkArray(double* values) -> void {
        this->m_values[0] = values[0];
        this->m_values[1] = values[1];
        this->m_values[2] = values[2];
        
        emit this->xChanged();
        emit this->yChanged();
        emit this->zChanged();
        
        this->notify();
    }

    auto Vector3::setX(qreal x) -> void {
        this->m_values[0] = x;
        emit this->xChanged();
        this->notify();
    }

    auto Vector3::getX() -> qreal {
        return this->m_values[0];
    }

    auto Vector3::setY(qreal y) -> void {
        this->m_values[1] = y;
        emit this->yChanged();
        this->notify();
    }

    auto Vector3::getY() -> qreal {
        return this->m_values[1];
    }

    auto Vector3::setZ(qreal z) -> void {
        this->m_values[2] = z;
        emit this->zChanged();
        this->notify();
    }

    auto Vector3::getZ() -> qreal {
        return this->m_values[2];
    }

    auto Vector3::getValues() -> array_t {
        return this->m_values;
    }
}
