#include "quickVtkVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<VolumeMapper> VolumeMapper::Register;

        VolumeMapper::VolumeMapper(vtkSmartPointer<vtkVolumeMapper> vtkObject) : AbstractVolumeMapper(vtkObject) {
        }
    }
}
