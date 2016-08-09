#include "quickVtkConeSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<ConeSource> ConeSource::Register;

        ConeSource::ConeSource() : PolyDataAlgorithm(vtkSmartPointer<vtkConeSource>::New()) {
            this->m_vtkObject = vtkConeSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_centerCb = [this](Math::Vector3&& vector) {
                this->updateCenter(std::move(vector));
            };

            this->m_directionCb = [this](Math::Vector3&& vector) {
                this->updateDirection(std::move(vector));
            };
        }

        auto ConeSource::setCenter(Math::Vector3* vector) -> void {
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

        auto ConeSource::getCenter() -> Math::Vector3* {
            if (!this->m_center) {
                auto center = this->m_vtkObject->GetCenter();
                this->setCenter(new Math::Vector3(center[0], center[1], center[2]));
            }

            return this->m_center;
        }

        auto ConeSource::setDirection(Math::Vector3* vector) -> void {
            if (this->m_direction) {
                this->m_direction->removeCallback(std::move(this->m_directionCb));
            }

            this->m_direction = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_directionCb));
                this->updateDirection(std::move(*vector));
            }

            emit this->directionChanged();
        }

        auto ConeSource::getDirection() -> Math::Vector3* {
            if (!this->m_direction) {
                auto direction = this->m_vtkObject->GetDirection();
                this->setDirection(new Math::Vector3(direction[0], direction[1], direction[2]));
            }

            return this->m_direction;
        }

        auto ConeSource::updateCenter(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetCenter(vector.getValues().data());
            this->update();
        }

        auto ConeSource::updateDirection(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetDirection(vector.getValues().data());
            this->update();
        }

        auto ConeSource::setHeight(float height) -> void {
            this->m_vtkObject->SetHeight(height);
            emit this->heightChanged();
            emit this->angleChanged();
            this->update();
        }

        auto ConeSource::getHeight() -> float {
            return this->m_vtkObject->GetHeight();
        }

        auto ConeSource::setRadius(float radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
            this->update();
        }

        auto ConeSource::getRadius() -> float {
            return this->m_vtkObject->GetRadius();
        }

        auto ConeSource::setAngle(float angle) -> void {
            this->m_vtkObject->SetAngle(angle);
            emit this->angleChanged();
            emit this->heightChanged();
            this->update();
        }

        auto ConeSource::getAngle() -> float {
            return this->m_vtkObject->GetAngle();
        }

        auto ConeSource::setResolution(int resolution) -> void {
            this->m_vtkObject->SetResolution(resolution);
            emit this->resolutionChanged();
            this->update();
        }

        auto ConeSource::getResolution() -> int {
            return this->m_vtkObject->GetResolution();
        }

        auto ConeSource::setCapping(bool capping) -> void {
            this->m_vtkObject->SetCapping(capping);
            emit this->cappingChanged();
            this->update();
        }

        auto ConeSource::getCapping() -> bool {
            return this->m_vtkObject->GetCapping();
        }

        ConeSource::~ConeSource() {
            if (this->m_center) {
                this->m_center->removeCallback(std::move(this->m_centerCb));
            }

            if (this->m_direction) {
                this->m_direction->removeCallback(std::move(this->m_directionCb));
            }
        }
    }
}