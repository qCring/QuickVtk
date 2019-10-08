#include "quickVtkPlane.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<Plane> Plane::Register(true);

        Plane::Plane() : ImplicitFunction(vtkSmartPointer<vtkPlane>::New()) {
            this->m_vtkObject = vtkPlane::SafeDownCast(ImplicitFunction::getVtkObject());

            this->m_origin = new Math::Vector3([this](){
                this->m_vtkObject->SetOrigin(this->m_origin->getValues().data());
                this->update();
            });

            this->m_normal = new Math::Vector3([this](){
                this->m_vtkObject->SetNormal(this->m_normal->getValues().data());
            });
        }

        auto Plane::getOrigin() -> Math::Vector3* {
            return this->m_origin;
        }

        auto Plane::getNormal() -> Math::Vector3* {
            return this->m_origin;
        }
    }
}
