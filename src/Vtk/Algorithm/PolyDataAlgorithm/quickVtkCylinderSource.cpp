#include "quickVtkCylinderSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<CylinderSource> CylinderSource::Register;

        CylinderSource::CylinderSource() : PolyDataAlgorithm(vtkSmartPointer<vtkCylinderSource>::New()) {
            this->m_vtkObject = vtkCylinderSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_centerCb = [this](Math::Vector3&& vector) {
                this->updateCenter(std::move(vector));
            };
        }

        auto CylinderSource::setCenter(Math::Vector3* vector) -> void {
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

        auto CylinderSource::getCenter() -> Math::Vector3* {
            if (!this->m_center) {
                auto center = this->m_vtkObject->GetCenter();
                this->setCenter(new Math::Vector3(center[0], center[1], center[2]));
            }

            return this->m_center;
        }

        auto CylinderSource::updateCenter(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetCenter(vector.getValues().data());
            this->update();
        }

        auto CylinderSource::setHeight(float height) -> void {
            this->m_vtkObject->SetHeight(height);
            emit this->heightChanged();
            this->update();
        }

        auto CylinderSource::getHeight() -> float {
            return this->m_vtkObject->GetHeight();
        }

        auto CylinderSource::setRadius(float radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
            this->update();
        }

        auto CylinderSource::getRadius() -> float {
            return this->m_vtkObject->GetRadius();
        }

        auto CylinderSource::setResolution(int resolution) -> void {
            this->m_vtkObject->SetResolution(resolution);
            emit this->resolutionChanged();
            this->update();
        }

        auto CylinderSource::getResolution() -> int {
            return this->m_vtkObject->GetResolution();
        }

        auto CylinderSource::setCapping(bool capping) -> void {
            this->m_vtkObject->SetCapping(capping);
            emit this->cappingChanged();
            this->update();
        }

        auto CylinderSource::getCapping() -> bool {
            return this->m_vtkObject->GetCapping();
        }

        CylinderSource::~CylinderSource() {
            if (this->m_center) {
                this->m_center->removeCallback(std::move(this->m_centerCb));
            }
        }
    }
}