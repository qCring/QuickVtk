#include "quickVtkSmartVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<SmartVolumeMapper> SmartVolumeMapper::Register;

        SmartVolumeMapper::SmartVolumeMapper() : VolumeMapper(this) {
            this->m_vtkSmartVolumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
            VolumeMapper::setVtkVolumeMapper(this->m_vtkSmartVolumeMapper);
        }

        SmartVolumeMapper::~SmartVolumeMapper() {
        }
    }
}
