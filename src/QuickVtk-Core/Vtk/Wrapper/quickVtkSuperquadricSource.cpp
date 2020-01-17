#include "quickVtkSuperquadricSource.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<SuperquadricSource> SuperquadricSource::Register(true);

        SuperquadricSource::SuperquadricSource() : PolyDataAlgorithm(vtkSmartPointer<vtkSuperquadricSource>::New()) {
            
            this->m_vtkObject = vtkSuperquadricSource::SafeDownCast(Algorithm::getVtkObject());
            
            this->m_center = new Math::Vector3([this](){
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });
            
            this->m_scale = new Math::Vector3([this](){
                this->m_vtkObject->SetScale(this->m_scale->getValues().data());
                this->update();
            });
        }
    
        auto SuperquadricSource::setToroidal(bool toroidal) -> void {
            this->m_vtkObject->SetToroidal(toroidal);
            this->update();
            emit this->toroidalChanged();
        }
    
        auto SuperquadricSource::getToroidal() -> bool {
            return this->m_vtkObject->GetToroidal();
        }
    
        auto SuperquadricSource::setThickness(qreal thickness) -> void {
            this->m_vtkObject->SetThickness(thickness);
            this->update();
            emit this->thicknessChanged();
        }
        
        auto SuperquadricSource::getThickness() -> qreal {
            return this->m_vtkObject->GetThickness();
        }
    
        auto SuperquadricSource::setSize(qreal size) -> void {
            this->m_vtkObject->SetSize(size);
            this->update();
            emit this->sizeChanged();
        }
        
        auto SuperquadricSource::getSize() -> qreal {
            return this->m_vtkObject->GetSize();
        }
    
        auto SuperquadricSource::setPhiRoundness(qreal phiRoundness) -> void {
            this->m_vtkObject->SetPhiRoundness(phiRoundness);
            this->update();
            emit this->phiRoundnessChanged();
        }
    
        auto SuperquadricSource::getPhiRoundness() -> qreal {
            return this->m_vtkObject->GetPhiRoundness();
        }
    
        auto SuperquadricSource::setThetaRoundness(qreal thetaRoundness) -> void {
            this->m_vtkObject->SetThetaRoundness(thetaRoundness);
            this->update();
            emit this->thetaRoundnessChanged();
        }
    
        auto SuperquadricSource::getThetaRoundness() -> qreal {
            return this->m_vtkObject->GetThetaRoundness();
        }
    
        auto SuperquadricSource::setPhiResolution(qreal phiResolution) -> void {
            this->m_vtkObject->SetPhiResolution(phiResolution);
            this->update();
            emit this->phiResolutionChanged();
        }
    
        auto SuperquadricSource::getPhiResolution() -> qreal {
            return this->m_vtkObject->GetPhiResolution();
        }
    
        auto SuperquadricSource::setThetaResolution(qreal thetaResolution) -> void {
            this->m_vtkObject->SetThetaResolution(thetaResolution);
            this->update();
            emit this->thetaResolutionChanged();
        }
    
        auto SuperquadricSource::getThetaResolution() -> qreal {
            return this->m_vtkObject->GetThetaResolution();
        }
    
        auto SuperquadricSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }
    
        auto SuperquadricSource::getScale() -> Math::Vector3* {
            return this->m_scale;
        }
    }
}
