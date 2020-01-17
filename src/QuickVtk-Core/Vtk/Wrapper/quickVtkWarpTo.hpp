#pragma once

#include "quickVtkPointSetAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkWarpTo.h>

namespace quick {
    namespace Vtk {

        class WarpTo : public PointSetAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* position READ getPosition CONSTANT);
            Q_PROPERTY(qreal scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(bool absolute READ getAbsolute WRITE setAbsolute NOTIFY absoluteChanged);
        private:
            static Qml::Register::Class<WarpTo> Register;
            vtkSmartPointer<vtkWarpTo> m_vtkObject = nullptr;
            Math::Vector3* m_position = nullptr;
        public:
            WarpTo();
            auto getPosition() -> Math::Vector3*;
            auto setScaleFactor(qreal) -> void;
            auto getScaleFactor() -> qreal;
            auto setAbsolute(bool) -> void;
            auto getAbsolute() -> bool;
        signals:
            void scaleFactorChanged();
            void absoluteChanged();
        };
    }
}
