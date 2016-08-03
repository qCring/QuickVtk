#include "quickVtkSmartVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<SmartVolumeMapper> SmartVolumeMapper::Register;

        SmartVolumeMapper::SmartVolumeMapper() : VolumeMapper(vtkSmartPointer<vtkSmartVolumeMapper>::New()) {
        }
    }
}
