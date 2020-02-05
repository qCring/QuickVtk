#pragma once

#include "quickVtkImplicitFunction.hpp"

#include <vtkCone.h>

namespace quick::Vtk {

    class Cone : public ImplicitFunction {
        Q_OBJECT
        Q_PROPERTY(qreal angle READ getAngle WRITE setAngle NOTIFY angleChanged);
    private:
        static Qml::Register::Class<Cone> Register;
        vtkSmartPointer<vtkCone> m_vtkObject = nullptr;
    public:
        Cone();
        auto setAngle(qreal) -> void;
        auto getAngle() -> qreal;
    signals:
        void angleChanged();
    };
}
