#include "quickVtkVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<VolumeMapper> VolumeMapper::Register;

        VolumeMapper::VolumeMapper() : AbstractVolumeMapper(this) {
            this->m_vtkVolumeMapper = nullptr;
        }

        VolumeMapper::VolumeMapper(VolumeMapper* other) : AbstractVolumeMapper(this) {
        }

        auto VolumeMapper::setVtkVolumeMapper(vtkSmartPointer<vtkVolumeMapper> vtkVolumeMapper) -> void {
            this->m_vtkVolumeMapper = vtkVolumeMapper;
            AbstractVolumeMapper::setVtkAbstractVolumeMapper(vtkVolumeMapper);
        }

        auto VolumeMapper::getVtkVolumeMapper() -> vtkSmartPointer<vtkVolumeMapper> {
            return this->m_vtkVolumeMapper;
        }

        VolumeMapper::~VolumeMapper() {
        }
    }
}
