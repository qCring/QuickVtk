#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkRotationalExtrusionFilter.h>

namespace quick {
    namespace Vtk {

        class RotationalExtrusionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged);
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
            Q_PROPERTY(qreal angle READ getAngle WRITE setAngle NOTIFY angleChanged);
            Q_PROPERTY(qreal translation READ getTranslation WRITE setTranslation NOTIFY translationChanged);
            Q_PROPERTY(qreal deltaRadius READ getDeltaRadius WRITE setDeltaRadius NOTIFY deltaRadiusChanged);
        private:
            static Qml::Register::Class<RotationalExtrusionFilter> Register;
            vtkSmartPointer<vtkRotationalExtrusionFilter> m_vtkObject = nullptr;
        public:
            RotationalExtrusionFilter();
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
            auto setAngle(qreal) -> void;
            auto getAngle() -> qreal;
            auto setTranslation(qreal) -> void;
            auto getTranslation() -> qreal;
            auto setDeltaRadius(qreal) -> void;
            auto getDeltaRadius() -> qreal;
        signals:
            void resolutionChanged();
            void cappingChanged();
            void angleChanged();
            void translationChanged();
            void deltaRadiusChanged();
        };
    }
}
