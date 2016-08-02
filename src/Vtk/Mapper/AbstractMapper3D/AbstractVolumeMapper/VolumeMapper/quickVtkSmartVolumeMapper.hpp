#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkSmartVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class SmartVolumeMapper : public VolumeMapper {
            Q_OBJECT
        private:
            static Qml::Register::Class<SmartVolumeMapper> Register;
            vtkSmartPointer<vtkSmartVolumeMapper> m_vtkSmartVolumeMapper;
        public:
            SmartVolumeMapper();
            ~SmartVolumeMapper();
        };
    }
}