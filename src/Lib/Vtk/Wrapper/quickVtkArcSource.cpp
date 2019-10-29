#include "quickVtkArcSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<ArcSource> ArcSource::Register(true);
    
        ArcSource::ArcSource() : PolyDataAlgorithm(vtkSmartPointer<vtkArcSource>::New()) {
            
            this->m_vtkObject = vtkArcSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector3([this]() {
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });

            this->m_point1 = new Math::Vector3([this]() {
                this->m_vtkObject->SetPoint1(this->m_point1->getValues().data());
                this->update();
            });
            
            this->m_point2 = new Math::Vector3([this]() {
                this->m_vtkObject->SetPoint2(this->m_point2->getValues().data());
                this->update();
            });
            
            this->m_center = new Math::Vector3([this]() {
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
            });
            
            this->m_polarVector = new Math::Vector3([this]() {
                this->m_vtkObject->SetPolarVector(this->m_polarVector->getValues().data());
            });
        }
    
        auto ArcSource::getPoint1() -> Math::Vector3* {
            return this->m_point1;
        }
    
        auto ArcSource::getPoint2() -> Math::Vector3* {
            return this->m_point2;
        }
    
        auto ArcSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }
    
        auto ArcSource::getPolarVector() -> Math::Vector3* {
            return this->m_polarVector;
        }
    
        auto ArcSource::setAngle(qreal angle) -> void {
            this->m_vtkObject->SetAngle(angle);
            emit this->angleChanged();
            this->update();
        }
    
        auto ArcSource::getAngle() -> qreal {
            return this->m_vtkObject->GetAngle();
        }
    
        auto ArcSource::setResolution(int resolution) -> void {
            this->m_vtkObject->SetResolution(resolution);
            emit this->resolutionChanged();
            this->update();
        }
    
        auto ArcSource::getResolution() -> int {
            return this->m_vtkObject->GetResolution();
        }
    
        auto ArcSource::setNegative(bool negative) -> void {
            this->m_vtkObject->SetNegative(negative);
            emit this->negativeChanged();
            this->update();
        }
    
        auto ArcSource::getNegative() -> bool {
            return this->m_vtkObject->GetNegative();
        }
    
        auto ArcSource::setUseNormalAndAngle(bool useNormalAndAngle) -> void {
            this->m_vtkObject->SetUseNormalAndAngle(useNormalAndAngle);
            emit this->useNormalAndAngleChanged();
            this->update();
        }
    
        auto ArcSource::getUseNormalAndAngle() -> bool {
            return this->m_vtkObject->GetUseNormalAndAngle();
        }
    }
}
