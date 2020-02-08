#include "quickVtkObject.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<Object> Object::Register(true);

    Object::Object(Type type) : m_type(type) {
    }

    auto Object::getType() -> Type {
        return this->m_type;
    }
}
