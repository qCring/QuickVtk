#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkShrinkPolyData.h>

namespace quick {

    namespace Vtk {

        class ShrinkPolyData : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(float shrinkFactor READ getShrinkFactor WRITE setShrinkFactor NOTIFY shrinkFactorChanged);
        private:
            static Qml::Register::Class<ShrinkPolyData> Register;
            vtkSmartPointer<vtkShrinkPolyData> m_vtkShrinkPolyData;
        public:
            ShrinkPolyData();
            auto setShrinkFactor(float) -> void;
            auto getShrinkFactor() -> float;
            ~ShrinkPolyData();
        signals:
            void shrinkFactorChanged();
        };
    }
}
