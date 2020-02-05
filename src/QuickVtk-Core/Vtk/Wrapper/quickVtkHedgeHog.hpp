#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkHedgeHog.h>

namespace quick::Vtk {

    class HedgeHog : public PolyDataAlgorithm {
        Q_OBJECT
    public:
        enum VectorMode {
            UseVector = VTK_USE_VECTOR,
            UseNormal = VTK_USE_NORMAL
        };
        Q_ENUM(VectorMode);
        Q_PROPERTY(qreal scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
        Q_PROPERTY(VectorMode vectorMode READ getVectorMode WRITE setVectorMode NOTIFY vectorModeChanged);
    private:
        static Qml::Register::Class<HedgeHog> Register;
        vtkSmartPointer<vtkHedgeHog> m_vtkObject = nullptr;
    public:
        HedgeHog();
        auto setScaleFactor(qreal) -> void;
        auto getScaleFactor() -> qreal;
        auto setVectorMode(VectorMode) -> void;
        auto getVectorMode() -> VectorMode;
    signals:
        void scaleFactorChanged();
        void vectorModeChanged();
    };
}
