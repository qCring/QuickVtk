#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkSphere.h>

namespace quick {

    namespace Vtk {

        class Sphere : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter WRITE setCenter NOTIFY centerChanged);
        private:
            static Qml::Register::Class<Sphere> Register;
            vtkSmartPointer<vtkSphere> m_vtkObject = nullptr;
            Math::Vector3::cb_t m_centerCb;
            Math::Vector3* m_center = nullptr;
        private:
            auto updateCenter(Math::Vector3&&) -> void;
        public:
            Sphere();
            auto setRadius(float) -> void;
            auto getRadius() -> float;
            auto setCenter(Math::Vector3*) -> void;
            auto getCenter() -> Math::Vector3*;
            ~Sphere();
        public slots:
            float evaluateFunction(float, float, float);
        signals:
            void radiusChanged();
            void centerChanged();
        };
    }
}