#include "quickVtkSphere.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<Sphere> Sphere::Register;

        Sphere::Sphere() : ImplicitFunction(vtkSmartPointer<vtkSphere>::New()) {
            this->m_vtkObject = vtkSphere::SafeDownCast(ImplicitFunction::getVtkObject());

            this->m_center = new Math::Vector3([this](){
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });
        }

        auto Sphere::getCenter() -> Math::Vector3* {
            return this->m_center;
        }

        float Sphere::evaluateFunction(float x, float y, float z) {
            return this->m_vtkObject->EvaluateFunction(x, y, z);
        }

        auto Sphere::setRadius(float radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
        }

        auto Sphere::getRadius() -> float {
            return this->m_vtkObject->GetRadius();
        }
    }
}