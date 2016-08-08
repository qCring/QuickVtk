#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkSmartVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class SmartVolumeMapper : public VolumeMapper {
            Q_OBJECT
            Q_PROPERTY(float finalColorWindow READ getFinalColorWindow WRITE setFinalColorWindow NOTIFY finalColorWindowChanged);
            Q_PROPERTY(float finalColorLevel READ getFinalColorLevel WRITE setFinalColorLevel NOTIFY finalColorLevelChanged);
        private:
            static Qml::Register::Class<SmartVolumeMapper> Register;
            vtkSmartPointer<vtkSmartVolumeMapper> m_vtkObject;
        public:
            SmartVolumeMapper();
            auto setFinalColorWindow(float) -> void;
            auto getFinalColorWindow() -> float;
            auto setFinalColorLevel(float) -> void;
            auto getFinalColorLevel() -> float;
        signals:
            void finalColorWindowChanged();
            void finalColorLevelChanged();
        };
    }
}