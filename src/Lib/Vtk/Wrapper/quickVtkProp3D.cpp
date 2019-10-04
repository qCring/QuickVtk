#include "quickVtkProp3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<Prop3D> Prop3D::Register;

        Prop3D::Prop3D(vtkSmartPointer<vtkProp3D> vtkObject) : Prop(vtkObject) {
            this->m_vtkObject = vtkProp3D::SafeDownCast(vtkObject);

            this->m_position = new Math::Vector3([this](){
                this->m_vtkObject->SetPosition(this->m_position->getValues().data());
                this->update();
            });

            this->m_origin = new Math::Vector3([this](){
                this->m_vtkObject->SetOrigin(this->m_origin->getValues().data());
                this->update();
            });

            this->m_orientation = new Math::Vector3([this](){
                this->m_vtkObject->SetOrientation(this->m_orientation->getValues().data());
                this->update();
            });

            this->m_scale = new Math::Vector3([this](){
                this->m_vtkObject->SetScale(this->m_scale->getValues().data());
                this->update();
            });
        }

        auto Prop3D::getPosition() -> Math::Vector3* {
            return this->m_position;
        }

        auto Prop3D::getOrientation() -> Math::Vector3* {
            return this->m_orientation;
        }

        auto Prop3D::getOrigin() -> Math::Vector3* {
            return this->m_origin;
        }

        auto Prop3D::getScale() -> Math::Vector3* {
            return this->m_scale;
        }
    }
}
