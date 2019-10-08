#include "quickVtkAbstractVolumeMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<AbstractVolumeMapper> AbstractVolumeMapper::Register(true);

        AbstractVolumeMapper::AbstractVolumeMapper(vtkSmartPointer<vtkAbstractVolumeMapper> vtkObject) : AbstractMapper3D(vtkObject) {
        }

        auto AbstractVolumeMapper::getVtkObject() -> vtkSmartPointer<vtkAbstractVolumeMapper> {
            return vtkAbstractVolumeMapper::SafeDownCast(Algorithm::getVtkObject());
        }
    }
}
