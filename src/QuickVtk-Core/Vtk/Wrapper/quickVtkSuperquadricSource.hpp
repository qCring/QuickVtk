#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkSuperquadricSource.h>

namespace quick {
    namespace Vtk {

        class SuperquadricSource : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum Axis {
                X,
                Y,
                Z
            };
        private:
            Q_ENUM(Axis);
            Q_PROPERTY(Axis axisOfSymmetry READ getAxisOfSymmetry WRITE setAxisOfSymmetry NOTIFY axisOfSymmetryChanged);
            Q_PROPERTY(bool toroidal READ getToroidal WRITE setToroidal NOTIFY toroidalChanged);
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* sccale READ getScale CONSTANT);
            Q_PROPERTY(qreal thickness READ getThickness WRITE setThickness NOTIFY thicknessChanged);
            Q_PROPERTY(qreal size READ getSize WRITE setSize NOTIFY sizeChanged);
            Q_PROPERTY(qreal phiRoundness READ getPhiRoundness WRITE setPhiRoundness NOTIFY phiRoundnessChanged);
            Q_PROPERTY(qreal thetaRoundness READ getThetaRoundness WRITE setThetaRoundness NOTIFY thetaRoundnessChanged);
            Q_PROPERTY(qreal phiResolution READ getPhiResolution WRITE setPhiResolution NOTIFY phiResolutionChanged);
            Q_PROPERTY(qreal thetaResolution READ getThetaResolution WRITE setThetaResolution NOTIFY thetaResolutionChanged);
        private:
            static Qml::Register::Class<SuperquadricSource> Register;
            vtkSmartPointer<vtkSuperquadricSource> m_vtkObject = nullptr;
            Math::Vector3* m_center = nullptr;
            Math::Vector3* m_scale = nullptr;
            Axis m_axisOfSymmetry;
        public:
            SuperquadricSource();
            auto setToroidal(bool) -> void;
            auto getToroidal() -> bool;
            auto setThickness(qreal) -> void;
            auto getThickness() -> qreal;
            auto setSize(qreal) -> void;
            auto getSize() -> qreal;
            auto setPhiRoundness(qreal) -> void;
            auto getPhiRoundness() -> qreal;
            auto setThetaRoundness(qreal) -> void;
            auto getThetaRoundness() -> qreal;
            auto setPhiResolution(qreal) -> void;
            auto getPhiResolution() -> qreal;
            auto setThetaResolution(qreal) -> void;
            auto getThetaResolution() -> qreal;
            auto setAxisOfSymmetry(Axis) -> void;
            auto getAxisOfSymmetry() -> Axis;
            auto getCenter() -> Math::Vector3*;
            auto getScale() -> Math::Vector3*;
        signals:
            void toroidalChanged();
            void thicknessChanged();
            void sizeChanged();
            void phiRoundnessChanged();
            void thetaRoundnessChanged();
            void phiResolutionChanged();
            void thetaResolutionChanged();
            void axisOfSymmetryChanged();
        };
    }
}

