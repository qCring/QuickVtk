#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkPointSource.h>

namespace quick {

    namespace Vtk {

        class PointSource : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum Distribution
            {
                UniformDistribution = VTK_POINT_UNIFORM,
                ShellDistribution = VTK_POINT_SHELL
            };
        private:
            Q_ENUM(Distribution);
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(Distribution distribution READ getDistribution WRITE setDistribution NOTIFY distributionChanged);
            Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
            Q_PROPERTY(double radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
        private:
            static Qml::Register::Symbol::Class<PointSource> Register;
            vtkSmartPointer<vtkPointSource> m_vtkObject;
            Math::Vector3* m_center;
        public:
            PointSource();
            auto setDistribution(Distribution) -> void;
            auto getDistribution() -> Distribution;
            auto setNumberOfPoints(int) -> void;
            auto getNumberOfPoints() -> int;
            auto setRadius(double) -> void;
            auto getRadius() -> double;
            auto getCenter() -> Math::Vector3*;
        signals:
            void distributionChanged();
            void numberOfPointsChanged();
            void radiusChanged();
        };
    }
}
