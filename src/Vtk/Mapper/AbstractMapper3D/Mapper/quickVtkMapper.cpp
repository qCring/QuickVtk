#include "quickVtkMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<Mapper> Mapper::Register;

        Mapper::Mapper(vtkSmartPointer<vtkMapper> vtkObject) : AbstractMapper3D(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto Mapper::getVtkObject() -> vtkSmartPointer<vtkMapper> {
            return vtkMapper::SafeDownCast(Algorithm::getVtkObject());
        }

        auto Mapper::setScalarMode(ScalarMode scalarMode) -> void {
            this->m_vtkObject->SetScalarMode(scalarMode);
            emit this->scalarModeChanged();
            this->update();
        }

        auto Mapper::getScalarMode() -> ScalarMode {
            return (ScalarMode) this->m_vtkObject->GetScalarMode();
        }

        auto Mapper::setScalarVisibility(bool val) -> void {
            this->m_vtkObject->SetScalarVisibility(val);
            emit this->scalarVisibilityChanged();
            this->update();
        }

        auto Mapper::getScalarVisibility() -> bool {
            return this->m_vtkObject->GetScalarVisibility();
        }
    }
}
