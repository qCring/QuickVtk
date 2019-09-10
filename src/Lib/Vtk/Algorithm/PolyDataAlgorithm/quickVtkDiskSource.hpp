#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkDiskSource.h>

namespace quick {

    namespace Vtk {

        class DiskSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(qreal innerRadius READ getInnerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged);
            Q_PROPERTY(qreal outerRadius READ getOuterRadius WRITE setOuterRadius NOTIFY outerRadiusChanged);
            Q_PROPERTY(int radialResolution READ getRadialResolution WRITE setRadialResolution NOTIFY radialResolutionChanged);
            Q_PROPERTY(int circumferentialResolution READ getCircumferentialResolution WRITE setCircumferentialResolution NOTIFY circumferentialResolutionChanged);
        private:
            static Qml::Register::Symbol::Class<DiskSource> Register;
            vtkSmartPointer<vtkDiskSource> m_vtkObject;
        public:
            DiskSource();
            auto setInnerRadius(qreal) -> void;
            auto setOuterRadius(qreal) -> void;
            auto setRadialResolution(int) -> void;
            auto setCircumferentialResolution(int) -> void ;
            auto getInnerRadius() -> qreal;
            auto getOuterRadius() -> qreal;
            auto getRadialResolution() -> int;
            auto getCircumferentialResolution() -> int;
        signals:
            void innerRadiusChanged();
            void outerRadiusChanged();
            void radialResolutionChanged();
            void circumferentialResolutionChanged();
        };
    }
}
