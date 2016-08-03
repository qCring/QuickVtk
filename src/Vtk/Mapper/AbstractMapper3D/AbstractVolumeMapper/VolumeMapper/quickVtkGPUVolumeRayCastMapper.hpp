#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkGPUVolumeRayCastMapper.h>

namespace quick {

    namespace Vtk {

        class GPUVolumeRayCastMapper : public VolumeMapper {
            Q_OBJECT
        private:
            static Qml::Register::Class<GPUVolumeRayCastMapper> Register;
        public:
            GPUVolumeRayCastMapper();
        };
    }
}