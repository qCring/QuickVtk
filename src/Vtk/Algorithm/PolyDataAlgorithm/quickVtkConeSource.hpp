#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkConeSource.h>

namespace quick {

    namespace Vtk {

        class ConeSource : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter WRITE setCenter NOTIFY centerChanged);
            Q_PROPERTY(quick::Math::Vector3* direction READ getDirection WRITE setDirection NOTIFY directionChanged);
            Q_PROPERTY(float height READ getHeight WRITE setHeight NOTIFY heightChanged);
            Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged);
            Q_PROPERTY(int resolution READ getResolution WRITE setResolution NOTIFY resolutionChanged)
            Q_PROPERTY(bool capping READ getCapping WRITE setCapping NOTIFY cappingChanged);
        private:
            static Qml::Register::Class<ConeSource> Register;
            vtkSmartPointer<vtkConeSource> m_vtkObject;
            Math::Vector3::cb_t m_centerCb;
            Math::Vector3::cb_t m_directionCb;
            Math::Vector3* m_center = nullptr;
            Math::Vector3* m_direction = nullptr;
        public:
            ConeSource();
            auto setCenter(Math::Vector3*) -> void;
            auto getCenter() -> Math::Vector3*;
            auto updateCenter(Math::Vector3&&) -> void;
            auto setDirection(Math::Vector3*) -> void;
            auto getDirection() -> Math::Vector3*;
            auto updateDirection(Math::Vector3&&) -> void;
            auto setHeight(float) -> void;
            auto getHeight() -> float;
            auto setRadius(float) -> void;
            auto getRadius() -> float;
            auto setAngle(float) -> void;
            auto getAngle() -> float;
            auto setResolution(int) -> void;
            auto getResolution() -> int;
            auto setCapping(bool) -> void;
            auto getCapping() -> bool;
            ~ConeSource();
        signals:
            void centerChanged();
            void directionChanged();
            void heightChanged();
            void angleChanged();
            void radiusChanged();
            void resolutionChanged();
            void cappingChanged();
        };
    }
}
