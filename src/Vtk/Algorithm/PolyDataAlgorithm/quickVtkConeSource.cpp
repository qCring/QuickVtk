#include "quickVtkConeSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<ConeSource> ConeSource::Register;

        ConeSource::ConeSource() : PolyDataAlgorithm(vtkSmartPointer<vtkConeSource>::New()) {
            this->m_vtkObject = vtkConeSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector3([this](){
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });

            this->m_direction = new Math::Vector3([this](){
                this->m_vtkObject->SetDirection(this->m_direction->getValues().data());
                this->update();
            });
        }

        auto ConeSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }

        auto ConeSource::getDirection() -> Math::Vector3* {
            return this->m_direction;
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
    }
}