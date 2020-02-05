#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkArrowSource.h>

namespace quick::Vtk {

    class ArrowSource : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(int tipResolution READ getTipResolution WRITE setTipResolution NOTIFY tipResolutionChanged);
        Q_PROPERTY(qreal tipLength READ getTipLength WRITE setTipLength NOTIFY tipLengthChanged);
        Q_PROPERTY(qreal tipRadius READ getTipRadius WRITE setTipRadius NOTIFY tipRadiusChanged);
        Q_PROPERTY(int shaftResolution READ getShaftResolution WRITE setShaftResolution NOTIFY shaftResolutionChanged);
        Q_PROPERTY(qreal shaftRadius READ getShaftRadius WRITE setShaftRadius NOTIFY shaftRadiusChanged);
        Q_PROPERTY(bool invert READ getInvert WRITE setInvert NOTIFY invertChanged);
    private:
        static Qml::Register::Class<ArrowSource> Register;
        vtkSmartPointer<vtkArrowSource> m_vtkObject = nullptr;
    public:
        ArrowSource();
        auto setTipResolution(int) -> void;
        auto getTipResolution() -> int;
        auto setTipLength(qreal) -> void;
        auto getTipLength() -> qreal;
        auto setTipRadius(qreal) -> void;
        auto getTipRadius() -> qreal;
        auto setShaftResolution(int) -> void;
        auto getShaftResolution() -> int;
        auto setShaftRadius(qreal) -> void;
        auto getShaftRadius() -> qreal;
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
