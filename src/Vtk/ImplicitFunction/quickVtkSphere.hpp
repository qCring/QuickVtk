#pragma once

#include "quickMathVector.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkSphere.h>

namespace quick {

    namespace Vtk {

        class Sphere : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(quick::Math::Vector* center READ getCenter WRITE setCenter NOTIFY centerChanged);
        private:
            static Qml::Register::VtkClass<Sphere> Register;
            vtkSmartPointer<vtkSphere> m_vtkSphere;
            Math::Vector::cb_t m_centerCb;
            Math::Vector* m_center;
        private:
            auto updateCenter(Math::Vector&&) -> void;
        public:
            Sphere();
            auto setVtkSphere(vtkSmartPointer<vtkSphere>) -> void;
            auto setRadius(float) -> void;
            auto getRadius() -> float;
            auto setCenter(Math::Vector*) -> void;
            auto getCenter() -> Math::Vector*;
            auto getVtkSphere() -> vtkSmartPointer<vtkSphere> ;
            ~Sphere();
        public slots:
            float evaluateFunction(float, float, float);
        signals:
            void radiusChanged();
            void centerChanged();
        };
    }
}