#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkRotationalExtrusionFilter.h>

namespace quick {

    namespace Vtk {

        class RotationalExtrusionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged);
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
            Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged);
            Q_PROPERTY(float translation READ getTranslation WRITE setTranslation NOTIFY translationChanged);
            Q_PROPERTY(float deltaRadius READ getDeltaRadius WRITE setDeltaRadius NOTIFY deltaRadiusChanged);
        private:
            static Qml::Register::Class<RotationalExtrusionFilter> Register;
            vtkSmartPointer<vtkRotationalExtrusionFilter> m_vtkObject;
        public:
            RotationalExtrusionFilter();
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
            auto setAngle(float) -> void;
            auto getAngle() -> float;
            auto setTranslation(float) -> void;
            auto getTranslation() -> float;
            auto setDeltaRadius(float) -> void;
            auto getDeltaRadius() -> float;
        signals:
            void resolutionChanged();
            void cappingChanged();
            void angleChanged();
            void translationChanged();
            void deltaRadiusChanged();
        };
    }
}
