#pragma once

#include "quickVtkProp.hpp"
#include "quickMathVector3.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp3D.h>

namespace quick {

    namespace Vtk {

        class Prop3D : public Prop {
            Q_OBJECT
            Q_PROPERTY(quick::Math::Vector3* scale READ getScale CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* origin READ getOrigin CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* position READ getPosition CONSTANT);
            Q_PROPERTY(quick::Math::Vector3* orientation READ getOrientation CONSTANT);
        private:
            static Qml::Register::Symbol::AbstractClass<Prop3D> Register;
            Math::Vector3* m_scale = nullptr;
            Math::Vector3* m_origin = nullptr;
            Math::Vector3* m_position = nullptr;
            Math::Vector3* m_orientation = nullptr;
            vtkSmartPointer<vtkProp3D> m_vtkObject;
        public:
            Prop3D(vtkSmartPointer<vtkProp3D>);
            auto getScale() -> Math::Vector3*;
            auto getOrigin() -> Math::Vector3*;
            auto getPosition() -> Math::Vector3*;
            auto getOrientation() -> Math::Vector3*;
        };
    }
}
