#include "quickVtkPlane.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<Plane> Plane::Register;

        Plane::Plane() : ImplicitFunction(vtkSmartPointer<vtkPlane>::New()) {
            this->m_vtkObject = vtkPlane::SafeDownCast(ImplicitFunction::getVtkObject());

            this->m_originCb = [this] (Math::Vector3&& vector) {
                this->updateOrigin(std::move(vector));
            };

            this->m_normalCb = [this] (Math::Vector3&& vector) {
                this->updateNormal(std::move(vector));
            };
        }

        auto Plane::updateOrigin(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetOrigin(vector.getValues().data());
            this->update();
        }

        auto Plane::updateNormal(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetNormal(vector.getValues().data());
            this->update();
        }

        auto Plane::setOrigin(Math::Vector3* vector) -> void {
            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }

            this->m_origin = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_originCb));
                this->updateOrigin(std::move(*vector));
            }

            emit this->originChanged();
        }

        auto Plane::getOrigin() -> Math::Vector3* {
            if (!this->m_origin) {
                auto origin = this->m_vtkObject->GetOrigin();
                this->setOrigin(new Math::Vector3(origin[0], origin[1], origin[2]));
            }

            return this->m_origin;
        }

        auto Plane::setNormal(Math::Vector3* vector) -> void {
            if (this->m_normal) {
                this->m_normal->removeCallback(std::move(this->m_normalCb));
            }

            this->m_normal = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_normalCb));
                this->updateNormal(std::move(*vector));
            }

            emit this->normalChanged();
        }

        auto Plane::getNormal() -> Math::Vector3* {
            if (!this->m_normal) {
                auto normal = this->m_vtkObject->GetNormal();
                this->setNormal(new Math::Vector3(normal[0], normal[1], normal[2]));
            }
            
            return this->m_origin;
        }

        Plane::~Plane() {
            if (this->m_normal) {
                this->m_normal->removeCallback(std::move(this->m_normalCb));
            }

            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }
        }
    }
}