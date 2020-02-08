#include "quickVtkAbstractVolumeMapper.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<AbstractVolumeMapper> AbstractVolumeMapper::Register(true);

    AbstractVolumeMapper::AbstractVolumeMapper(vtkSmartPointer<vtkAbstractVolumeMapper> vtkObject) : AbstractMapper3D(vtkObject) {
    }

    auto AbstractVolumeMapper::getVtkObject() -> vtkSmartPointer<vtkAbstractVolumeMapper> {
        return vtkAbstractVolumeMapper::SafeDownCast(Algorithm::getVtkObject());
    }
}
