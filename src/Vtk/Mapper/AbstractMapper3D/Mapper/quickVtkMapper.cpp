#include "quickVtkMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Mapper> Mapper::Register;

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

        auto Mapper::setScalarMode(ScalarMode val) -> void {
            this->m_scalarMode = val;
            this->m_vtkMapper->SetScalarMode(val);
            emit this->scalarModeChanged();
            this->update();
        }

        auto Mapper::getScalarMode() -> ScalarMode {
            return this->m_scalarMode;
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
