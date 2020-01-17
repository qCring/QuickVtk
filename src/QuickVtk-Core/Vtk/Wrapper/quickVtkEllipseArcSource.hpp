#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkEllipseArcSource.h>

namespace quick {
    namespace Vtk {

        class EllipseArcSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* normal READ getNormal CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* majorRadiusVector READ getMajorRadiusVector CONSTANT);
            Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged);
            Q_PROPERTY(qreal segmentAngle READ getSegmentAngle WRITE setSegmentAngle NOTIFY segmentAngleChanged);
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged);
            Q_PROPERTY(qreal ratio READ getRatio WRITE setRatio NOTIFY ratioChanged);
        private:
            static Qml::Register::Class<EllipseArcSource> Register;
            vtkSmartPointer<vtkEllipseArcSource> m_vtkObject = nullptr;
            Math::Vector3* m_center = nullptr;
            Math::Vector3* m_normal = nullptr;
            Math::Vector3* m_majorRadiusVector = nullptr;
        public:
            EllipseArcSource();
            auto getCenter() -> Math::Vector3*;
            auto getNormal() -> Math::Vector3*;
            auto getMajorRadiusVector() -> Math::Vector3*;
            auto setStartAngle(qreal) -> void;
            auto getStartAngle() -> qreal;
            auto setSegmentAngle(qreal) -> void;
            auto getSegmentAngle() -> qreal;
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setRatio(qreal) -> void;
            auto getRatio() -> qreal;
        signals:
            void startAngleChanged();
            void segmentAngleChanged();
            void resolutionChanged();
            void ratioChanged();
        };
    }
}
