#pragma once

#include "quickVtkPointSetAlgorithm.hpp"

#include <vtkWarpScalar.h>

namespace quick {

    namespace Vtk {

        class WarpScalar : public PointSetAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(bool useNormal READ getUseNormal WRITE setUseNormal NOTIFY useNormalChanged);
        private:
            static Qml::Register::Symbol::Class<WarpScalar> Register;
            vtkSmartPointer<vtkWarpScalar> m_vtkObject;
        public:
            WarpScalar();
            auto setScaleFactor(qreal) -> void;
            auto getScaleFactor() -> qreal;
            auto setUseNormal(bool) -> void;
            auto getUseNormal() -> bool;
        signals:
            void scaleFactorChanged();
            void useNormalChanged();
        };
    }
}
