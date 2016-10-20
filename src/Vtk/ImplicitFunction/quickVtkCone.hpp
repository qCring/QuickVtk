#pragma once

#include "quickVtkImplicitFunction.hpp"

#include <vtkCone.h>

namespace quick {

    namespace Vtk {

        class Cone : public ImplicitFunction {
            Q_OBJECT
            Q_PROPERTY(float angle READ getAngle WRITE setAngle NOTIFY angleChanged);
        private:
            static Qml::Register::Symbol::Class<Cone> Register;
            vtkSmartPointer<vtkCone> m_vtkObject = nullptr;
        public:
            Cone();
            auto setAngle(float) -> void;
            auto getAngle() -> float;
        signals:
            void angleChanged();
        };
    }
}
