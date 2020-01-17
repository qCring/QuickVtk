#include "quickVtkSectorSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<SectorSource> SectorSource::Register(true);

        SectorSource::SectorSource() : PolyDataAlgorithm(vtkSmartPointer<vtkSectorSource>::New()) {
            this->m_vtkObject = vtkSectorSource::SafeDownCast(Algorithm::getVtkObject());
        }

        auto SectorSource::setInnerRadius(qreal radius) -> void {
            this->m_vtkObject->SetInnerRadius(radius);
            emit this->innerRadiusChanged();
            this->update();
        }

        auto SectorSource::getInnerRadius() -> qreal {
            return this->m_vtkObject->GetInnerRadius();
        }

        auto SectorSource::setOuterRadius(qreal radius) -> void {
            this->m_vtkObject->SetOuterRadius(radius);
            emit this->outerRadiusChanged();
            this->update();
        }
    
        auto SectorSource::getOuterRadius() -> qreal {
            return this->m_vtkObject->GetOuterRadius();
        }

        auto SectorSource::setRadialResolution(int value) -> void {
            this->m_vtkObject->SetRadialResolution(value);
            emit this->radialResolutionChanged();
            this->update();
        }
    
        auto SectorSource::getRadialResolution() -> int {
            return this->m_vtkObject->GetRadialResolution();
        }

        auto SectorSource::setCircumferentialResolution(int value) -> void {
            this->m_vtkObject->SetCircumferentialResolution(value);
            emit this->circumferentialResolutionChanged();
            this->update();
        }
    
        auto SectorSource::getCircumferentialResolution() -> int {
            return this->m_vtkObject->GetCircumferentialResolution();
        }
    
        auto SectorSource::setStartAngle(qreal startAngle) -> void {
            this->m_vtkObject->SetStartAngle(startAngle);
            this->update();
            emit this->startAngleChanged();
        }
    
        auto SectorSource::getStartAngle() -> qreal {
            return this->m_vtkObject->GetStartAngle();
        }
    
        auto SectorSource::setEndAngle(qreal endAngle) -> void {
            this->m_vtkObject->SetEndAngle(endAngle);
            this->update();
            emit this->endAngleChanged();
        }
    
        auto SectorSource::getEndAngle() -> qreal {
            return this->m_vtkObject->GetEndAngle();
        }
    
        auto SectorSource::setZCoord(qreal zCoord) -> void {
            this->m_vtkObject->SetZCoord(zCoord);
            this->update();
            emit this->zCoordChanged();
        }
    
        auto SectorSource::getZCoord() -> qreal {
            return this->m_vtkObject->GetZCoord();
        }
    }
}
