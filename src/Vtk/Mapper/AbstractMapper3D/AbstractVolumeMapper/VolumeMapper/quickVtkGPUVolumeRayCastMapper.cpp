#include "quickVtkGPUVolumeRayCastMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<GPUVolumeRayCastMapper> GPUVolumeRayCastMapper::Register;

        GPUVolumeRayCastMapper::GPUVolumeRayCastMapper() : VolumeMapper(vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New()) {
        }
    }
}
