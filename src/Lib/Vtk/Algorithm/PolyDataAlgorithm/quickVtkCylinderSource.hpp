#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkCylinderSource.h>

namespace quick {

    namespace Vtk {

        class CylinderSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(float height READ getHeight WRITE setHeight NOTIFY heightChanged);
            Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged)
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
        private:
            static Qml::Register::Symbol::Class<CylinderSource> Register;
            vtkSmartPointer<vtkCylinderSource> m_vtkObject;
            Math::Vector3* m_center = nullptr;
        public:
            CylinderSource();
            auto getCenter() -> Math::Vector3*;
            auto setHeight(float) -> void;
            auto getHeight() -> float;
            auto setRadius(float) -> void;
            auto getRadius() -> float;
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
        signals:
            void heightChanged();
            void radiusChanged();
            void resolutionChanged();
            void cappingChanged();
        };
    }
}
