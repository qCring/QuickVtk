#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkDiskSource.h>

namespace quick {

    namespace Vtk {

        class DiskSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(float innerRadius READ getInnerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged);
            Q_PROPERTY(float outerRadius READ getOuterRadius WRITE setOuterRadius NOTIFY outerRadiusChanged);
            Q_PROPERTY(int radialResolution READ getRadialResolution WRITE setRadialResolution NOTIFY radialResolutionChanged);
            Q_PROPERTY(int circumferentialResolution READ getCircumferentialResolution WRITE setCircumferentialResolution NOTIFY circumferentialResolutionChanged);
        private:
            static Qml::Register::VtkClass<DiskSource> Register;
            vtkSmartPointer<vtkDiskSource> m_vtkDiskSource;
        public:
            DiskSource();
            auto setInnerRadius(float) -> void;
            auto setOuterRadius(float) -> void;
            auto setRadialResolution(int) -> void;
            auto setCircumferentialResolution(int) -> void ;
            auto getInnerRadius() -> float;
            auto getOuterRadius() -> float;
            auto getRadialResolution() -> int;
            auto getCircumferentialResolution() -> int;
            ~DiskSource();
        signals:
            void innerRadiusChanged();
            void outerRadiusChanged();
            void radialResolutionChanged();
            void circumferentialResolutionChanged();
        };
    }
}
