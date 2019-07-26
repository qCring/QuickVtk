#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkHedgeHog.h>

namespace quick {

    namespace Vtk {

        class HedgeHog : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum VectorMode {
                UseVector = VTK_USE_VECTOR,
                UseNormal = VTK_USE_NORMAL
            };
            Q_ENUM(VectorMode);
            Q_PROPERTY(float scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(VectorMode vectorMode READ getVectorMode WRITE setVectorMode NOTIFY vectorModeChanged);
        private:
            static Qml::Register::Symbol::Class<HedgeHog> Register;
            vtkSmartPointer<vtkHedgeHog> m_vtkObject;
        public:
            HedgeHog();
            auto setScaleFactor(float) -> void;
            auto getScaleFactor() -> float;
            auto setVectorMode(VectorMode) -> void;
            auto getVectorMode() -> VectorMode;
        signals:
            void scaleFactorChanged();
            void vectorModeChanged();
        };
    }
}
