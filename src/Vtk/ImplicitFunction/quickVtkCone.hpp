#pragma once

#include "quickVtkImplicitFunction.hpp"

#include <vtkCone.h>

namespace quick {

    namespace Vtk {

        class Cone : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged);
        private:
            static Qml::Register::Class<Cone> Register;
            vtkSmartPointer<vtkCone> m_vtkCone;
        public:
            Cone();
            auto setVtkCone(vtkSmartPointer<vtkCone>) -> void;
            auto setAngle(float) -> void;
            auto getAngle() -> float;
            auto getVtkCone() -> vtkSmartPointer<vtkCone> ;
            ~Cone();
        signals:
            void angleChanged();
        };
    }
}