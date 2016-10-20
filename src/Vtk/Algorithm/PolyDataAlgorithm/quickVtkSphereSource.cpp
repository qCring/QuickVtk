#include "quickVtkSphereSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<SphereSource> SphereSource::Register;

        SphereSource::SphereSource() : PolyDataAlgorithm(vtkSmartPointer<vtkSphereSource>::New()) {
            this->m_vtkObject = vtkSphereSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector3([this](){
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });
        }

        auto SphereSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }

        auto SphereSource::setLatLongTessellation(bool value) -> void {
            this->m_vtkObject->SetLatLongTessellation(value);
            emit this->latLongTessellationChanged();
            this->update();
        }

        auto SphereSource::setRadius(float radius) -> void {
            this->m_vtkObject->SetRadius(radius);
            emit this->radiusChanged();
            this->update();
        }

        auto SphereSource::setThetaResolution(int value) -> void {
            this->m_vtkObject->SetThetaResolution(value);
            emit this->thetaResolutionChanged();
            this->update();
        }

        auto SphereSource::setPhiResolution(int value) -> void {
            this->m_vtkObject->SetPhiResolution(value);
            emit this->phiResolutionChanged();
            this->update();
        }

        auto SphereSource::setStartTheta(float value) -> void {
            this->m_vtkObject->SetStartTheta(value);
            emit this->startThetaChanged();
            this->update();
        }

        auto SphereSource::setStartPhi(float value) -> void {
            this->m_vtkObject->SetStartPhi(value);
            emit this->startPhiChanged();
            this->update();
        }

        auto SphereSource::setEndTheta(float value) -> void {
            this->m_vtkObject->SetEndTheta(value);
            emit this->endThetaChanged();
            this->update();
        }

        auto SphereSource::setEndPhi(float value) -> void {
            this->m_vtkObject->SetEndPhi(value);
            emit this->endPhiChanged();
            this->update();
        }

        auto SphereSource::getLatLongTessellation() -> bool {
            return this->m_vtkObject->GetLatLongTessellation();
        }

        auto SphereSource::getThetaResolution() -> int {
            return this->m_vtkObject->GetThetaResolution();
        }

        auto SphereSource::getPhiResolution() -> int {
            return this->m_vtkObject->GetPhiResolution();
        }

        auto SphereSource::getStartTheta() -> float {
            return this->m_vtkObject->GetStartTheta();
        }

        auto SphereSource::getStartPhi() -> float {
            return this->m_vtkObject->GetStartPhi();
        }

        auto SphereSource::getEndTheta() -> float {
            return this->m_vtkObject->GetEndTheta();
        }

        auto SphereSource::getEndPhi() -> float {
            return this->m_vtkObject->GetEndPhi();
        }

        auto SphereSource::getRadius() -> float {
            return this->m_vtkObject->GetRadius();
        }
    }
}
