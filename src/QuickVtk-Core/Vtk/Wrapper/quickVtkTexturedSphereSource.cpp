#include "quickVtkTexturedSphereSource.hpp"

namespace quick::Vtk {

    Qml::Register::Class<TexturedSphereSource> TexturedSphereSource::Register(true);

    TexturedSphereSource::TexturedSphereSource() : PolyDataAlgorithm(vtkSmartPointer<vtkTexturedSphereSource>::New()) {
        this->m_vtkObject = vtkTexturedSphereSource::SafeDownCast(Algorithm::getVtkObject());
    }
    
    auto TexturedSphereSource::setRadius(qreal radius) -> void {
        this->m_vtkObject->SetRadius(radius);
        emit this->radiusChanged();
        this->update();
    }
    
    auto TexturedSphereSource::getRadius() -> qreal {
        return this->m_vtkObject->GetRadius();
    }
    
    auto TexturedSphereSource::setTheta(qreal theta) -> void {
        this->m_vtkObject->SetTheta(theta);
        emit this->thetaChanged();
        this->update();
    }
    
    auto TexturedSphereSource::getTheta() -> qreal {
        return this->m_vtkObject->GetTheta();
    }
    
    auto TexturedSphereSource::setPhi(qreal phi) -> void {
        this->m_vtkObject->SetPhi(phi);
        emit this->phiChanged();
        this->update();
    }
    
    auto TexturedSphereSource::getPhi() -> qreal {
        return this->m_vtkObject->GetPhi();
    }
    
    auto TexturedSphereSource::setThetaResolution(int thetaResolution) -> void {
        this->m_vtkObject->SetThetaResolution(thetaResolution);
        emit this->thetaResolutionChanged();
        this->update();
    }
    
    auto TexturedSphereSource::getThetaResolution() -> int {
        return this->m_vtkObject->GetThetaResolution();
    }
    
    auto TexturedSphereSource::setPhiResolution(int phiResolution) -> void {
        this->m_vtkObject->SetPhiResolution(phiResolution);
        emit this->phiResolutionChanged();
        this->update();
    }
    
    auto TexturedSphereSource::getPhiResolution() -> int {
        return this->m_vtkObject->GetPhiResolution();
    }
}
