#include "quickVtkAbstractVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<AbstractVolumeMapper> AbstractVolumeMapper::Register;

        AbstractVolumeMapper::AbstractVolumeMapper() : AbstractMapper3D(this) {
            this->m_vtkAbstractVolumeMapper = nullptr;
        }

        AbstractVolumeMapper::AbstractVolumeMapper(AbstractVolumeMapper* other) : AbstractMapper3D(this) {
        }

        auto AbstractVolumeMapper::setVtkAbstractVolumeMapper(vtkSmartPointer<vtkAbstractVolumeMapper> vtkAbstractVolumeMapper) -> void {
            this->m_vtkAbstractVolumeMapper = vtkAbstractVolumeMapper;
            AbstractMapper3D::setVtkAbstractMapper3D(vtkAbstractVolumeMapper);
        }

        auto AbstractVolumeMapper::getVtkAbstractVolumeMapper() -> vtkSmartPointer<vtkAbstractVolumeMapper> {
            return this->m_vtkAbstractVolumeMapper;
        }

        AbstractVolumeMapper::~AbstractVolumeMapper() {
        }
    }
}
