#include "quickVtkSphere.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<Sphere> Sphere::Register;

        Sphere::Sphere() : ImplicitFunction(this) {
            this->setVtkSphere(vtkSmartPointer<vtkSphere>::New());

            this->m_centerCb = [this] (Math::Vector3&& vector) {
                this->updateCenter(std::move(vector));
            };
        }

        auto Sphere::setVtkSphere(vtkSmartPointer<vtkSphere> vtkSphere) -> void {
            this->m_vtkSphere = vtkSphere;

            ImplicitFunction::setVtkImplicitFunction(vtkSphere);
        }

        auto Sphere::updateCenter(Math::Vector3&& vector) -> void {
            this->m_vtkSphere->SetCenter(vector.getValues().data());
            this->update();
        }

        auto Sphere::setCenter(Math::Vector3* vector) -> void {
            if (this->m_center) {
                this->m_center->removeCallback(std::move(this->m_centerCb));
            }

            this->m_center = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_centerCb));
                this->updateCenter(std::move(*vector));
            }

            emit this->centerChanged();
        }

        auto Sphere::getCenter() -> Math::Vector3* {
            if (!this->m_center) {
                auto center = this->m_vtkSphere->GetCenter();
                this->setCenter(new Math::Vector3(center[0], center[1], center[2]));
            }

            return this->m_center;
        }

        float Sphere::evaluateFunction(float x, float y, float z) {
            return this->m_vtkSphere->EvaluateFunction(x, y, z);
        }

        auto Sphere::setRadius(float radius) -> void {
            this->m_vtkSphere->SetRadius(radius);
            emit this->radiusChanged();
        }

        auto Sphere::getRadius() -> float {
            return this->m_vtkSphere->GetRadius();
        }

        auto Sphere::getVtkSphere() -> vtkSmartPointer<vtkSphere> {
            return this->m_vtkSphere;
        }

        Sphere::~Sphere() {
            this->m_vtkSphere = 0;
        }
    }
}