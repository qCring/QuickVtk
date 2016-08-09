#pragma once

#include "quickVtkPointSetAlgorithm.hpp"
#include "quickMathVector3.hpp"

#include <vtkWarpTo.h>

namespace quick {

    namespace Vtk {

        class WarpTo : public PointSetAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* position READ getPosition WRITE setPosition NOTIFY positionChanged);
            Q_PROPERTY(float scaleFactor READ getScaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged);
            Q_PROPERTY(bool absolute READ getAbsolute WRITE setAbsolute NOTIFY absoluteChanged);
        private:
            static Qml::Register::Class<WarpTo> Register;
            vtkSmartPointer<vtkWarpTo> m_vtkObject;
            Math::Vector3* m_position = nullptr;
            Math::Vector3::cb_t m_positionCb;
        private:
            auto updatePosition(Math::Vector3&&) -> void;
        public:
            WarpTo();
            auto setPosition(Math::Vector3*) -> void;
            auto getPosition() -> Math::Vector3*;
            auto setScaleFactor(float) -> void;
            auto getScaleFactor() -> float;
            auto setAbsolute(bool) -> void;
            auto getAbsolute() -> bool;
        signals:
            void positionChanged();
            void scaleFactorChanged();
            void absoluteChanged();
        };
    }
}
