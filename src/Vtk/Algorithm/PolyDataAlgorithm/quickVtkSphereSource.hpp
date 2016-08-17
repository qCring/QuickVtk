#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkSphereSource.h>

namespace quick {

    namespace Vtk {

        class SphereSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
            Q_PROPERTY(bool latLongTessellation READ getLatLongTessellation WRITE setLatLongTessellation NOTIFY latLongTessellationChanged);
            Q_PROPERTY(int thetaResolution READ getThetaResolution WRITE setThetaResolution NOTIFY thetaResolutionChanged);
            Q_PROPERTY(int phiResolution READ getPhiResolution WRITE setPhiResolution NOTIFY phiResolutionChanged);
            Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(float startTheta READ getStartTheta WRITE setStartTheta NOTIFY startThetaChanged);
            Q_PROPERTY(float startPhi READ getStartPhi WRITE setStartPhi NOTIFY startPhiChanged);
            Q_PROPERTY(float endTheta READ getEndTheta WRITE setEndTheta NOTIFY endThetaChanged);
            Q_PROPERTY(float endPhi READ getEndPhi WRITE setEndPhi NOTIFY endPhiChanged);
        private:
            static Qml::Register::Class<SphereSource> Register;
            vtkSmartPointer<vtkSphereSource> m_vtkObject;
            Math::Vector3* m_center = nullptr;
        public:
            SphereSource();
            auto getCenter() -> Math::Vector3*;
            auto setLatLongTessellation(bool) -> void;
            auto getLatLongTessellation() -> bool;
            auto setRadius(float) -> void;
            auto getRadius() -> float;
            auto setThetaResolution(int) -> void;
            auto getThetaResolution() -> int;
            auto setPhiResolution(int) -> void;
            auto getPhiResolution() -> int;
            auto setStartTheta(float) -> void;
            auto getStartTheta() -> float;
            auto setStartPhi(float) -> void;
            auto getStartPhi() -> float;
            auto setEndTheta(float) -> void;
            auto getEndTheta() -> float;
            auto setEndPhi(float) -> void;
            auto getEndPhi() -> float;
        signals:
            void latLongTessellationChanged();
            void thetaResolutionChanged();
            void phiResolutionChanged();
            void startThetaChanged();
            void startPhiChanged();
            void endThetaChanged();
            void endPhiChanged();
            void radiusChanged();
        };
    }
}
