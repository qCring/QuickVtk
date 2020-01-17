#include "quickVtkSphereSource.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<SphereSource> SphereSource::Register(true);

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

        auto SphereSource::setRadius(qreal radius) -> void {
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

        auto SphereSource::setStartTheta(qreal value) -> void {
            this->m_vtkObject->SetStartTheta(value);
            emit this->startThetaChanged();
            this->update();
        }

        auto SphereSource::setStartPhi(qreal value) -> void {
            this->m_vtkObject->SetStartPhi(value);
            emit this->startPhiChanged();
            this->update();
        }

        auto SphereSource::setEndTheta(qreal value) -> void {
            this->m_vtkObject->SetEndTheta(value);
            emit this->endThetaChanged();
            this->update();
        }

        auto SphereSource::setEndPhi(qreal value) -> void {
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

        auto SphereSource::getStartTheta() -> qreal {
            return this->m_vtkObject->GetStartTheta();
        }

        auto SphereSource::getStartPhi() -> qreal {
            return this->m_vtkObject->GetStartPhi();
        }

        auto SphereSource::getEndTheta() -> qreal {
            return this->m_vtkObject->GetEndTheta();
        }

        auto SphereSource::getEndPhi() -> qreal {
            return this->m_vtkObject->GetEndPhi();
        }

        auto SphereSource::getRadius() -> qreal {
            return this->m_vtkObject->GetRadius();
        }
    }
}
