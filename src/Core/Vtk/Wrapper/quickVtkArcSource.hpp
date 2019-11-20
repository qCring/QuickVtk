#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkArcSource.h>

namespace quick {

    namespace Vtk {

        class ArcSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* point1 READ getPoint1 CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* point2 READ getPoint2 CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* polarVector READ getPolarVector CONSTANT);
            Q_PROPERTY(qreal angle READ getAngle WRITE setAngle NOTIFY angleChanged);
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged);
            Q_PROPERTY(bool negative READ getNegative WRITE setNegative NOTIFY negativeChanged);
            Q_PROPERTY(bool useNormalAndAngle READ getUseNormalAndAngle WRITE setUseNormalAndAngle NOTIFY useNormalAndAngleChanged);
        private:
            static Qml::Register::Class<ArcSource> Register;
            vtkSmartPointer<vtkArcSource> m_vtkObject = nullptr;
            Math::Vector3* m_point1 = nullptr;
            Math::Vector3* m_point2 = nullptr;
            Math::Vector3* m_center = nullptr;
            Math::Vector3* m_polarVector = nullptr;
        public:
            ArcSource();
            auto getPoint1() -> Math::Vector3*;
            auto getPoint2() -> Math::Vector3*;
            auto getCenter() -> Math::Vector3*;
            auto getPolarVector() -> Math::Vector3*;
            auto setAngle(qreal) -> void;
            auto getAngle() -> qreal;
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setNegative(bool) -> void;
            auto getNegative() -> bool;
            auto setUseNormalAndAngle(bool) -> void;
            auto getUseNormalAndAngle() -> bool;
        signals:
            void angleChanged();
            void resolutionChanged();
            void negativeChanged();
            void useNormalAndAngleChanged();
        };
    }
}
