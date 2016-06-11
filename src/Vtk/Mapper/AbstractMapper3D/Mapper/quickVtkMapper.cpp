#include "quickVtkMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkAbstractClass<Mapper> Mapper::Register;

        Mapper::Mapper() : AbstractMapper3D(this) {
            this->m_vtkMapper = nullptr;
        }

        Mapper::Mapper(Mapper* other) : AbstractMapper3D(this) {
        }

        auto Mapper::setVtkMapper(vtkSmartPointer<vtkMapper> vtkMapper) -> void {
            this->m_vtkMapper = vtkMapper;
            AbstractMapper3D::setVtkAbstractMapper3D(vtkMapper);
        }

        auto Mapper::getVtkMapper() -> vtkSmartPointer<vtkMapper> {
            return this->m_vtkMapper;
        }

        auto Mapper::setScalarMode(ScalarMode scalarMode) -> void {
            this->m_vtkMapper->SetScalarMode(scalarMode);
            emit this->scalarModeChanged();
            this->update();
        }

        auto Mapper::getScalarMode() -> ScalarMode {
            return (ScalarMode) this->m_vtkMapper->GetScalarMode();
        }

        auto Mapper::setScalarVisibility(bool val) -> void {
            this->m_vtkMapper->SetScalarVisibility(val);
            emit this->scalarVisibilityChanged();
            this->update();
        }

        auto Mapper::getScalarVisibility() -> bool {
            return this->m_vtkMapper->GetScalarVisibility();
        }

        Mapper::~Mapper() {
        }
    }
}
