#include "quickVtkProp3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Prop3D> Prop3D::Register;

        Prop3D::Prop3D() : Prop(this) {
        }

        Prop3D::Prop3D(Prop3D* other) : Prop(this) {
        }

        auto Prop3D::setVtkProp3D(vtkSmartPointer<vtkProp3D> vtkProp3D) -> void {
            this->m_vtkProp3D = vtkProp3D;
            Prop::setVtkProp(vtkProp3D);
        }

        auto Prop3D::getVtkProp3D() -> vtkSmartPointer<vtkProp3D> {
            return this->m_vtkProp3D;
        }

        Prop3D::~Prop3D() {
            this->m_vtkProp3D = 0;
        }
    }
}