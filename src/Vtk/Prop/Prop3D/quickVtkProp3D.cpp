#include "quickVtkProp3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Prop3D> Prop3D::Register;

        Prop3D::Prop3D() : Prop(this) {
        }

        Prop3D::Prop3D(Prop3D* other) : Prop(this) {
            this->m_positionCb = [this] (Math::Vector&& vector) {
                this->updatePosition(std::move(vector));
            };

            this->m_originCb = [this] (Math::Vector&& vector) {
                this->updateOrigin(std::move(vector));
            };

            this->m_orientationCb = [this] (Math::Vector&& vector) {
                this->updateOrientation(std::move(vector));
            };

            this->m_scaleCb = [this] (Math::Vector&& vector) {
                this->updateScale(std::move(vector));
            };
        }

        auto Prop3D::updateScale(Math::Vector&& vector) -> void {
            this->m_vtkProp3D->SetScale(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updateOrigin(Math::Vector&& vector) -> void {
            this->m_vtkProp3D->SetOrigin(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updateOrientation(Math::Vector&& vector) -> void {
            this->m_vtkProp3D->SetOrientation(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updatePosition(Math::Vector&& vector) -> void {
            this->m_vtkProp3D->SetPosition(vector.getValues().data());
            this->update();
        }

        auto Prop3D::setScale(Math::Vector* vector) -> void {
            if (this->m_scale) {
                this->m_scale->removeCallback(std::move(this->m_scaleCb));
            }

            this->m_scale = vector;

            if (vector) {
                vector->setCallback(std::move(this->m_scaleCb));
                this->updateScale(std::move(*vector));
            }
        }

        auto Prop3D::getScale() -> Math::Vector* {
            if (!this->m_scale) {
                auto scale = this->m_vtkProp3D->GetScale();
                this->setScale(new Math::Vector(scale[0], scale[1], scale[2]));
            }

            return this->m_scale;
        }

        auto Prop3D::setPosition(Math::Vector* vector) -> void {
            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionCb));
            }

            this->m_position = vector;

            if (vector) {
                vector->setCallback(std::move(this->m_positionCb));
                this->updatePosition(std::move(*vector));
            }
        }

        auto Prop3D::getPosition() -> Math::Vector* {
            if (!this->m_position) {
                auto position = this->m_vtkProp3D->GetPosition();
                this->setPosition(new Math::Vector(position[0], position[1], position[2]));
            }

            return this->m_position;
        }

        auto Prop3D::setOrientation(Math::Vector* vector) -> void {
            if (this->m_orientation) {
                this->m_orientation->removeCallback(std::move(this->m_orientationCb));
            }

            this->m_orientation = vector;

            if (vector) {
                vector->setCallback(std::move(this->m_orientationCb));
                this->updateOrientation(std::move(*vector));
            }
        }

        auto Prop3D::getOrientation() -> Math::Vector* {
            if (!this->m_orientation) {
                auto orientation = this->m_vtkProp3D->GetOrientation();
                this->setOrientation(new Math::Vector(orientation[0], orientation[1], orientation[2]));
            }

            return this->m_orientation;
        }

        auto Prop3D::setOrigin(Math::Vector* vector) -> void {
            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }

            this->m_origin = vector;

            if (vector) {
                vector->setCallback(std::move(this->m_originCb));
                this->updateOrigin(std::move(*vector));
            }
        }

        auto Prop3D::getOrigin() -> Math::Vector* {
            if (!this->m_origin) {
                auto origin = this->m_vtkProp3D->GetOrigin();
                this->setOrigin(new Math::Vector(origin[0], origin[1], origin[2]));
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
            if (this->m_scale) {
                this->m_scale->removeCallback(std::move(this->m_scaleCb));
            }

            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }

            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionCb));
            }

            if (this->m_orientation) {
                this->m_orientation->removeCallback(std::move(this->m_orientationCb));
            }
        }
    }
}