#pragma once

#include "quickMathVector3.hpp"
#include "quickVtkImplicitFunction.hpp"

#include <vtkPlane.h>

namespace quick::Vtk {

    class Plane : public ImplicitFunction {
        Q_OBJECT
        Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* normal READ getNormal CONSTANT);
    private:
        static Qml::Register::Class<Plane> Register;
        vtkSmartPointer<vtkPlane> m_vtkObject = nullptr;
        Math::Vector3* m_origin = nullptr;
        Math::Vector3* m_normal = nullptr;
    public:
        Plane();
        auto getOrigin() -> Math::Vector3*;
        auto getNormal() -> Math::Vector3*;
    };
}
