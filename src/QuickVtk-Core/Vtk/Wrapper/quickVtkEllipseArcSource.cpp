#include "quickVtkEllipseArcSource.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<EllipseArcSource> EllipseArcSource::Register(true);
    
        EllipseArcSource::EllipseArcSource() : PolyDataAlgorithm(vtkSmartPointer<vtkEllipseArcSource>::New()) {
            
            this->m_vtkObject = vtkEllipseArcSource::SafeDownCast(Algorithm::getVtkObject());

            this->m_center = new Math::Vector3([this]() {
                this->m_vtkObject->SetCenter(this->m_center->getValues().data());
                this->update();
            });
            
            this->m_normal = new Math::Vector3([this]() {
                this->m_vtkObject->SetNormal(this->m_normal->getValues().data());
                this->update();
            });
            
            this->m_majorRadiusVector = new Math::Vector3([this]() {
                this->m_vtkObject->SetMajorRadiusVector(this->m_majorRadiusVector->getValues().data());
                this->update();
            });
        }
    
        auto EllipseArcSource::getCenter() -> Math::Vector3* {
            return this->m_center;
        }
    
        auto EllipseArcSource::getNormal() -> Math::Vector3* {
            return this->m_normal;
        }
    
        auto EllipseArcSource::getMajorRadiusVector() -> Math::Vector3* {
            return this->m_majorRadiusVector;
        }
    
        auto EllipseArcSource::setStartAngle(qreal startAngle) -> void {
            this->m_vtkObject->SetStartAngle(startAngle);
            emit this->startAngleChanged();
            this->update();
        }
    
        auto EllipseArcSource::getStartAngle() -> qreal {
            return this->m_vtkObject->GetStartAngle();
        }
    
        auto EllipseArcSource::setSegmentAngle(qreal segmentAngle) -> void {
            this->m_vtkObject->SetSegmentAngle(segmentAngle);
            emit this->segmentAngleChanged();
            this->update();
        }
    
        auto EllipseArcSource::getSegmentAngle() -> qreal {
            return this->m_vtkObject->GetSegmentAngle();
        }
    
        auto EllipseArcSource::setResolution(int resolution) -> void {
            this->m_vtkObject->SetResolution(resolution);
            emit this->resolutionChanged();
            this->update();
        }
    
        auto EllipseArcSource::getResolution() -> int {
            return this->m_vtkObject->GetResolution();
        }
    
        auto EllipseArcSource::setRatio(qreal ratio) -> void {
            this->m_vtkObject->SetRatio(ratio);
            emit this->ratioChanged();
            this->update();
        }
    
        auto EllipseArcSource::getRatio() -> qreal {
            return this->m_vtkObject->GetRatio();
        }
    }
}
