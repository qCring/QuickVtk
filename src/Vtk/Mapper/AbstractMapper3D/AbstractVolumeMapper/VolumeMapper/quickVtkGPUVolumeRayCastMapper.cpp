#include "quickVtkGPUVolumeRayCastMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<GPUVolumeRayCastMapper> GPUVolumeRayCastMapper::Register;

        GPUVolumeRayCastMapper::GPUVolumeRayCastMapper() : VolumeMapper(this) {
            this->m_vtkGPUVolumeRayCastMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
            VolumeMapper::setVtkVolumeMapper(this->m_vtkGPUVolumeRayCastMapper);
        }

        GPUVolumeRayCastMapper::~GPUVolumeRayCastMapper() {
        }
    }
}
