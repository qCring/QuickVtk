#include "quickVtkSphereSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<SphereSource> SphereSource::Register;

        SphereSource::SphereSource() : PolyDataAlgorithm(this) {
            this->m_vtkSphereSource = vtkSmartPointer<vtkSphereSource>::New();

            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkSphereSource);

            this->m_centerCb = [this](Math::Vector&& vector) {
                this->updateCenter(std::move(vector));
            };
        }

        auto SphereSource::setCenter(Math::Vector* vector) -> void {
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

        auto SphereSource::getCenter() -> Math::Vector* {
            if (!this->m_center) {
                auto center = this->m_vtkSphereSource->GetCenter();
                this->setCenter(new Math::Vector(center[0], center[1], center[2]));
            }

            return this->m_center;
        }

        auto SphereSource::updateCenter(Math::Vector&& vector) -> void {
            this->m_vtkSphereSource->SetCenter(vector.getValues().data());
            this->update();
        }

        auto SphereSource::setLatLongTessellation(bool value) -> void {
            this->m_vtkSphereSource->SetLatLongTessellation(value);
            emit this->latLongTessellationChanged();
            this->update();
        }

        auto SphereSource::setRadius(float radius) -> void {
            this->m_vtkSphereSource->SetRadius(radius);
            emit this->radiusChanged();
            this->update();
        }

        auto SphereSource::setThetaResolution(int value) -> void {
            this->m_vtkSphereSource->SetThetaResolution(value);
            emit this->thetaResolutionChanged();
            this->update();
        }

        auto SphereSource::setPhiResolution(int value) -> void {
            this->m_vtkSphereSource->SetPhiResolution(value);
            emit this->phiResolutionChanged();
            this->update();
        }

        auto SphereSource::setStartTheta(float value) -> void {
            this->m_vtkSphereSource->SetStartTheta(value);
            emit this->startThetaChanged();
            this->update();
        }

        auto SphereSource::setStartPhi(float value) -> void {
            this->m_vtkSphereSource->SetStartPhi(value);
            emit this->startPhiChanged();
            this->update();
        }

        auto SphereSource::setEndTheta(float value) -> void {
            this->m_vtkSphereSource->SetEndTheta(value);
            emit this->endThetaChanged();
            this->update();
        }

        auto SphereSource::setEndPhi(float value) -> void {
            this->m_vtkSphereSource->SetEndPhi(value);
            emit this->endPhiChanged();
            this->update();
        }

        auto SphereSource::getLatLongTessellation() -> bool {
            return this->m_vtkSphereSource->GetLatLongTessellation();
        }

        auto SphereSource::getThetaResolution() -> int {
            return this->m_vtkSphereSource->GetThetaResolution();
        }

        auto SphereSource::getPhiResolution() -> int {
            return this->m_vtkSphereSource->GetPhiResolution();
        }

        auto SphereSource::getStartTheta() -> float {
            return this->m_vtkSphereSource->GetStartTheta();
        }

        auto SphereSource::getStartPhi() -> float {
            return this->m_vtkSphereSource->GetStartPhi();
        }

        auto SphereSource::getEndTheta() -> float {
            return this->m_vtkSphereSource->GetEndTheta();
        }

        auto SphereSource::getEndPhi() -> float {
            return this->m_vtkSphereSource->GetEndPhi();
        }

        auto SphereSource::getRadius() -> float {
            return this->m_vtkSphereSource->GetRadius();
        }

        SphereSource::~SphereSource() {
            if (this->m_center) {
                this->m_center->removeCallback(std::move(this->m_centerCb));
            }

            this->m_vtkSphereSource = nullptr;
        }
    }
}