#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkTexturedSphereSource.h>

namespace quick::Vtk {

    class TexturedSphereSource : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
        Q_PROPERTY(qreal theta READ getTheta WRITE setTheta NOTIFY thetaChanged);
        Q_PROPERTY(qreal phi READ getPhi WRITE setPhi NOTIFY phiChanged);
        Q_PROPERTY(int thetaResolution READ getThetaResolution WRITE setThetaResolution NOTIFY thetaResolutionChanged);
        Q_PROPERTY(int phiResolution READ getPhiResolution WRITE setPhiResolution NOTIFY phiResolutionChanged);
    private:
        static Qml::Register::Class<TexturedSphereSource> Register;
        vtkSmartPointer<vtkTexturedSphereSource> m_vtkObject = nullptr;
    public:
        TexturedSphereSource();
        auto setRadius(qreal) -> void;
        auto getRadius() -> qreal;
        auto setTheta(qreal) -> void;
        auto getTheta() -> qreal;
        auto setPhi(qreal) -> void;
        auto getPhi() -> qreal;
        auto setThetaResolution(int) -> void;
        auto getThetaResolution() -> int;
        auto setPhiResolution(int) -> void;
        auto getPhiResolution() -> int;
    signals:
        void radiusChanged();
        void thetaChanged();
        void phiChanged();
        void thetaResolutionChanged();
        void phiResolutionChanged();
    };
}
