#include "quickVtkProp3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Prop3D> Prop3D::Register;

        Prop3D::Prop3D() : Prop(this) {
        }

        Prop3D::Prop3D(Prop3D* other) : Prop(this) {
            this->m_positionChanged = [this](Math::Vector&& vector) {
                m_vtkProp3D->SetPosition(vector.getValues().data());
                this->update();
            };

            this->m_originChanged = [this](Math::Vector&& vector) {
                m_vtkProp3D->SetOrigin(vector.getValues().data());
            };
        }

        auto Prop3D::setPosition(Math::Vector* vector) -> void {
            if (this->m_position) {
                delete this->m_position;
            }

            this->m_position = vector;

            if (vector) {
                vector->onChange(std::move(this->m_positionChanged));
            }
        }

        auto Prop3D::setOrigin(Math::Vector* vector) -> void {
            if (this->m_origin) {
                delete this->m_origin;
            }

            this->m_origin = vector;

            if (vector) {
                vector->onChange(std::move(this->m_originChanged));
            }
        }

        auto Prop3D::getPosition() -> Math::Vector* {
            if (!this->m_position) {
                this->setPosition(new Math::Vector()); // todo: init from this->m_vtkProp3D->GetPosition();
            }

            return this->m_position;
        }

        auto Prop3D::getOrigin() -> Math::Vector* {
            if (!this->m_origin) {
                this->setOrigin(new Math::Vector()); // todo: init from this->m_vtkProp3D->GetOrigin();
            }

            return this->m_origin;
        }

        auto Prop3D::setVtkProp3D(vtkSmartPointer<vtkProp3D> vtkProp3D) -> void {
            this->m_vtkProp3D = vtkProp3D;
            Prop::setVtkProp(vtkProp3D);
        }

        auto Prop3D::getVtkProp3D() -> vtkSmartPointer<vtkProp3D> {
            return this->m_vtkProp3D;
        }

        Prop3D::~Prop3D() {
            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionChanged));
            }

            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originChanged));
            }

            this->m_vtkProp3D = 0;
        }
    }
}