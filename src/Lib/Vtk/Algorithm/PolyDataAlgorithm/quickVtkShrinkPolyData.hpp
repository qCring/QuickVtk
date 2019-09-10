#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkShrinkPolyData.h>

namespace quick {

    namespace Vtk {

        class ShrinkPolyData : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal shrinkFactor READ getShrinkFactor WRITE setShrinkFactor NOTIFY shrinkFactorChanged);
        private:
            static Qml::Register::Symbol::Class<ShrinkPolyData> Register;
            vtkSmartPointer<vtkShrinkPolyData> m_vtkObject;
        public:
            ShrinkPolyData();
            auto setShrinkFactor(qreal) -> void;
            auto getShrinkFactor() -> qreal;
        signals:
            void shrinkFactorChanged();
        };
    }
}
