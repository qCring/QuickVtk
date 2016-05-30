#pragma once

#include "quickVtkProp.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp3D.h>

namespace quick {

    namespace Vtk {

        class Prop3D : public Prop {
            Q_OBJECT
        private:
            static Qml::Register::VtkClass<Prop3D> Register;
            vtkSmartPointer<vtkProp3D> m_vtkProp3D;
        public:
            Prop3D();
            Prop3D(Prop3D*);
            auto setVtkProp3D(vtkSmartPointer<vtkProp3D>) -> void;
            auto getVtkProp3D() -> vtkSmartPointer<vtkProp3D>;
            virtual ~Prop3D();
        };
    }
}