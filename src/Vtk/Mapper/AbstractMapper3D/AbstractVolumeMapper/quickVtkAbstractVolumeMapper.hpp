#pragma once

#include "quickVtkAbstractMapper3D.hpp"

#include <vtkAbstractVolumeMapper.h>

namespace quick {

    namespace Vtk {

        class ScalarsToColors;

        class AbstractVolumeMapper : public AbstractMapper3D {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<AbstractVolumeMapper> Register;
            vtkSmartPointer<vtkAbstractVolumeMapper> m_vtkAbstractVolumeMapper;
        public:
            AbstractVolumeMapper();
            AbstractVolumeMapper(AbstractVolumeMapper*);
            auto setVtkAbstractVolumeMapper(vtkSmartPointer<vtkAbstractVolumeMapper>) -> void;
            auto getVtkAbstractVolumeMapper() -> vtkSmartPointer<vtkAbstractVolumeMapper>;
            ~AbstractVolumeMapper();
        signals:
        };
    }
}