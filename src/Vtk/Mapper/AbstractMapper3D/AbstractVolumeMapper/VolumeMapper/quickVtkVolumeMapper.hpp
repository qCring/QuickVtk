#pragma once

#include "quickVtkAbstractVolumeMapper.hpp"

#include <vtkVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class VolumeMapper : public AbstractVolumeMapper {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<VolumeMapper> Register;
            vtkSmartPointer<vtkVolumeMapper> m_vtkVolumeMapper;
        public:
            VolumeMapper();
            VolumeMapper(VolumeMapper*);
            auto setVtkVolumeMapper(vtkSmartPointer<vtkVolumeMapper>) -> void;
            auto getVtkVolumeMapper() -> vtkSmartPointer<vtkVolumeMapper>;
            ~VolumeMapper();
        };
    }
}