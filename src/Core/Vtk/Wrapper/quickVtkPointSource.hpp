#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"
#include "quickVtkRandomSequence.hpp"
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
            Q_PROPERTY(quick::Vtk::RandomSequence* randomSequence READ getRandomSequence WRITE setRandomSequence NOTIFY randomSequenceChanged);
            Q_PROPERTY(int numberOfPoints READ getNumberOfPoints WRITE setNumberOfPoints NOTIFY numberOfPointsChanged);
            Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
        private:
            static Qml::Register::Class<PointSource> Register;
            vtkSmartPointer<vtkPointSource> m_vtkObject;
            Math::Vector3* m_center;
            RandomSequence* m_randomSequence;
        public:
            PointSource();
            auto setDistribution(Distribution) -> void;
            auto getDistribution() -> Distribution;
            auto setNumberOfPoints(int) -> void;
            auto getNumberOfPoints() -> int;
            auto setRadius(qreal) -> void;
            auto getRadius() -> qreal;
            auto getCenter() -> Math::Vector3*;
            auto setRandomSequence(RandomSequence*) -> void;
            auto getRandomSequence() -> RandomSequence*;
        signals:
            void randomSequenceChanged();
            void distributionChanged();
            void numberOfPointsChanged();
            void radiusChanged();
        };
    }
}
