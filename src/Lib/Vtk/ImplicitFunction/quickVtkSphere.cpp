#include "quickVtkSphere.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<Sphere> Sphere::Register;

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

        qreal Sphere::evaluateFunction(qreal x, qreal y, qreal z) {
            return this->m_vtkObject->EvaluateFunction(x, y, z);
        }

        auto Sphere::setRadius(qreal radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
        }

        auto Sphere::getRadius() -> qreal {
            return this->m_vtkObject->GetRadius();
        }
    }
}
