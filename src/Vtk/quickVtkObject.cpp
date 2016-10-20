#include "quickVtkObject.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<Object> Object::Register;

        Object::Object(Type type) : m_type(type) {
        }

        auto Object::getType() -> Type {
            return this->m_type;
        }
    }
}
