#pragma once

#include "quickVtkVolumeMapper.hpp"

#include <vtkSmartVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class SmartVolumeMapper : public VolumeMapper {
            Q_OBJECT
            Q_PROPERTY(qreal finalColorWindow READ getFinalColorWindow WRITE setFinalColorWindow NOTIFY finalColorWindowChanged);
            Q_PROPERTY(qreal finalColorLevel READ getFinalColorLevel WRITE setFinalColorLevel NOTIFY finalColorLevelChanged);
        private:
            static Qml::Register::Class<SmartVolumeMapper> Register;
            vtkSmartPointer<vtkSmartVolumeMapper> m_vtkObject;
        public:
            SmartVolumeMapper();
            auto setFinalColorWindow(qreal) -> void;
            auto getFinalColorWindow() -> qreal;
            auto setFinalColorLevel(qreal) -> void;
            auto getFinalColorLevel() -> qreal;
        signals:
            void finalColorWindowChanged();
            void finalColorLevelChanged();
        };
    }
}
