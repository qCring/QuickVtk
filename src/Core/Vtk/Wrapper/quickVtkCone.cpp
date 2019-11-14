#include "quickVtkCone.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<Cone> Cone::Register(true);

        Cone::Cone() : ImplicitFunction(vtkSmartPointer<vtkCone>::New()) {
            this->m_vtkObject = vtkCone::SafeDownCast(ImplicitFunction::getVtkObject());
        }

        auto Cone::setAngle(qreal angle) -> void {
            this->m_vtkObject->SetAngle(angle);
            emit this->angleChanged();
        }

        auto Cone::getAngle() -> qreal {
            return this->m_vtkObject->GetAngle();
        }
    }
}
