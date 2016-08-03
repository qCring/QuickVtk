#pragma once

#include "quickVtkAbstractVolumeMapper.hpp"

#include <vtkVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class VolumeMapper : public AbstractVolumeMapper {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<VolumeMapper> Register;
        public:
            VolumeMapper(vtkSmartPointer<vtkVolumeMapper>);
        };
    }
}