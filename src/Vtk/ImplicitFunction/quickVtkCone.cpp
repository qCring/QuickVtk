#include "quickVtkCone.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<Cone> Cone::Register;

        Cone::Cone() : ImplicitFunction(this) {
            this->setVtkCone(vtkSmartPointer<vtkCone>::New());
        }

        auto Cone::setVtkCone(vtkSmartPointer<vtkCone> vtkCone) -> void {
            this->m_vtkCone = vtkCone;

            ImplicitFunction::setVtkImplicitFunction(vtkCone);
        }

        auto Cone::setAngle(float angle) -> void {
            this->m_vtkCone->SetAngle(angle);
            emit this->angleChanged();
        }

        auto Cone::getAngle() -> float {
            return this->m_vtkCone->GetAngle();
        }

        auto Cone::getVtkCone() -> vtkSmartPointer<vtkCone> {
            return this->m_vtkCone;
        }

        Cone::~Cone() {
            this->m_vtkCone = 0;
        }
    }
}