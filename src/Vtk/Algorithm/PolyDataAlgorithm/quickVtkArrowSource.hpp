#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkArrowSource.h>

namespace quick {

    namespace Vtk {

        class ArrowSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int tipResolution READ getTipResolution WRITE setTipResolution NOTIFY tipResolutionChanged);
            Q_PROPERTY(double tipLength READ getTipLength WRITE setTipLength NOTIFY tipLengthChanged);
            Q_PROPERTY(double tipRadius READ getTipRadius WRITE setTipRadius NOTIFY tipRadiusChanged);
            Q_PROPERTY(int shaftResolution READ getShaftResolution WRITE setShaftResolution NOTIFY shaftResolutionChanged);
            Q_PROPERTY(double shaftRadius READ getShaftRadius WRITE setShaftRadius NOTIFY shaftRadiusChanged);
            Q_PROPERTY(bool invert READ getInvert WRITE setInvert NOTIFY invertChanged);
        private:
            static Qml::Register::Class<ArrowSource> Register;
            vtkSmartPointer<vtkArrowSource> m_vtkObject;
        public:
            ArrowSource();
            auto setTipResolution(int) -> void;
            auto getTipResolution() -> int;
            auto setTipLength(double) -> void;
            auto getTipLength() -> double;
            auto setTipRadius(double) -> void;
            auto getTipRadius() -> double;
            auto setShaftResolution(int) -> void;
            auto getShaftResolution() -> int;
            auto setShaftRadius(double) -> void;
            auto getShaftRadius() -> double;
            auto setInvert(bool) -> void;
            auto getInvert() -> bool;
        signals:
            void tipResolutionChanged();
            void tipLengthChanged();
            void tipRadiusChanged();
            void shaftResolutionChanged();
            void shaftRadiusChanged();
            void invertChanged();
        };
    }
}
