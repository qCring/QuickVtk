#include "quickVtkDiskSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<DiskSource> DiskSource::Register(true);

        DiskSource::DiskSource() : PolyDataAlgorithm(vtkSmartPointer<vtkDiskSource>::New()) {
            this->m_vtkObject = vtkDiskSource::SafeDownCast(Algorithm::getVtkObject());
        }

        auto DiskSource::setInnerRadius(qreal radius) -> void {
            this->m_vtkObject->SetInnerRadius(radius);
            emit this->innerRadiusChanged();
            this->update();
        }

        auto DiskSource::setOuterRadius(qreal radius) -> void {
            this->m_vtkObject->SetOuterRadius(radius);
            emit this->outerRadiusChanged();
            this->update();
        }

        auto DiskSource::setRadialResolution(int value) -> void {
            this->m_vtkObject->SetRadialResolution(value);
            emit this->radialResolutionChanged();
            this->update();
        }

        auto DiskSource::setCircumferentialResolution(int value) -> void {
            this->m_vtkObject->SetCircumferentialResolution(value);
            emit this->circumferentialResolutionChanged();
            this->update();
        }

        auto DiskSource::getInnerRadius() -> qreal {
            return this->m_vtkObject->GetInnerRadius();
        }

        auto DiskSource::getOuterRadius() -> qreal {
            return this->m_vtkObject->GetOuterRadius();
        }

        auto DiskSource::getRadialResolution() -> int {
            return this->m_vtkObject->GetRadialResolution();
        }

        auto DiskSource::getCircumferentialResolution() -> int {
            return this->m_vtkObject->GetCircumferentialResolution();
        }
    }
}
