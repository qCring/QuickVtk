#pragma once

#include "quickVtkAbstractMapper3D.hpp"

#include <vtkAbstractVolumeMapper.h>

namespace quick::Vtk {

    class AbstractVolumeMapper : public AbstractMapper3D {
        Q_OBJECT
    private:
        static Qml::Register::AbstractClass<AbstractVolumeMapper> Register;
    public:
        AbstractVolumeMapper(vtkSmartPointer<vtkAbstractVolumeMapper>);
        auto getVtkObject() -> vtkSmartPointer<vtkAbstractVolumeMapper>;
    };
}
