#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkShrinkPolyData.h>

namespace quick {
    namespace Vtk {

        class ShrinkPolyData : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal shrinkFactor READ getShrinkFactor WRITE setShrinkFactor NOTIFY shrinkFactorChanged);
        private:
            static Qml::Register::Class<ShrinkPolyData> Register;
            vtkSmartPointer<vtkShrinkPolyData> m_vtkObject = nullptr;
        public:
            ShrinkPolyData();
            auto setShrinkFactor(qreal) -> void;
            auto getShrinkFactor() -> qreal;
        signals:
            void shrinkFactorChanged();
        };
    }
}
