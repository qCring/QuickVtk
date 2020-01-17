#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkSectorSource.h>

namespace quick {

    namespace Vtk {

        class SectorSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal innerRadius READ getInnerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged);
            Q_PROPERTY(qreal outerRadius READ getOuterRadius WRITE setOuterRadius NOTIFY outerRadiusChanged);
            Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged);
            Q_PROPERTY(qreal endAngle READ getEndAngle WRITE setEndAngle NOTIFY endAngleChanged);
            Q_PROPERTY(qreal zCoord READ getZCoord WRITE setZCoord NOTIFY zCoordChanged);
            Q_PROPERTY(int radialResolution READ getRadialResolution WRITE setRadialResolution NOTIFY radialResolutionChanged);
            Q_PROPERTY(int circumferentialResolution READ getCircumferentialResolution WRITE setCircumferentialResolution NOTIFY circumferentialResolutionChanged);
        private:
            static Qml::Register::Class<SectorSource> Register;
            vtkSmartPointer<vtkSectorSource> m_vtkObject = nullptr;
        public:
            SectorSource();
            auto setInnerRadius(qreal) -> void;
            auto getInnerRadius() -> qreal;
            auto setOuterRadius(qreal) -> void;
            auto getOuterRadius() -> qreal;
            auto setRadialResolution(int) -> void;
            auto getRadialResolution() -> int;
            auto setCircumferentialResolution(int) -> void ;
            auto getCircumferentialResolution() -> int;
            auto setStartAngle(qreal) -> void;
            auto getStartAngle() -> qreal;
            auto setEndAngle(qreal) -> void;
            auto getEndAngle() -> qreal;
            auto setZCoord(qreal) -> void;
            auto getZCoord() -> qreal;
        signals:
            void innerRadiusChanged();
            void outerRadiusChanged();
            void radialResolutionChanged();
            void circumferentialResolutionChanged();
            void startAngleChanged();
            void endAngleChanged();
            void zCoordChanged();
        };
    }
}
