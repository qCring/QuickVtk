#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkSphere.h>

namespace quick {

    namespace Vtk {

        class Sphere : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(qreal radius READ getRadius WRITE setRadius NOTIFY radiusChanged);
            Q_PROPERTY(quick::Math::Vector3* center READ getCenter CONSTANT);
        private:
            static Qml::Register::Symbol::Class<Sphere> Register;
            vtkSmartPointer<vtkSphere> m_vtkObject = nullptr;
            Math::Vector3* m_center = nullptr;
        public:
            Sphere();
            auto setRadius(qreal) -> void;
            auto getRadius() -> qreal;
            auto setCenter(Math::Vector3*) -> void;
            auto getCenter() -> Math::Vector3*;
        public slots:
            qreal evaluateFunction(qreal, qreal, qreal);
        signals:
            void radiusChanged();
        };
    }
}
