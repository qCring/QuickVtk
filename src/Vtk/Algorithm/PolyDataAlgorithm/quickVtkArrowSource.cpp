#include "quickVtkArrowSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<ArrowSource> ArrowSource::Register;

        ArrowSource::ArrowSource() : PolyDataAlgorithm(vtkSmartPointer<vtkArrowSource>::New()) {
            this->m_vtkObject = vtkArrowSource::SafeDownCast(Algorithm::getVtkObject());
        }

        auto ArrowSource::setTipResolution(int tipResolution) -> void {
            this->m_vtkObject->SetTipResolution(tipResolution);
            emit this->tipResolutionChanged();
            this->update();
        }

        auto ArrowSource::getTipResolution() -> int {
            return this->m_vtkObject->GetTipResolution();
        }

        auto ArrowSource::setTipLength(double tipLength) -> void {
            this->m_vtkObject->SetTipLength(tipLength);
            emit this->tipLengthChanged();
            this->update();
        }

        auto ArrowSource::getTipLength() -> double {
            return this->m_vtkObject->GetTipLength();
        }

        auto ArrowSource::setTipRadius(double tipRadius) -> void {
            this->m_vtkObject->SetTipRadius(tipRadius);
            emit this->tipRadiusChanged();
            this->update();
        }

        auto ArrowSource::getTipRadius() -> double {
            return this->m_vtkObject->GetTipRadius();
        }

        auto ArrowSource::setShaftResolution(int shaftResolution) -> void {
            this->m_vtkObject->SetShaftResolution(shaftResolution);
            emit this->shaftResolutionChanged();
            this->update();
        }

        auto ArrowSource::getShaftResolution() -> int {
            return this->m_vtkObject->GetShaftResolution();
        }

        auto ArrowSource::setShaftRadius(double shaftRadius) -> void {
            this->m_vtkObject->SetShaftRadius(shaftRadius);
            emit this->shaftRadiusChanged();
            this->update();
        }

        auto ArrowSource::getShaftRadius() -> double {
            return this->m_vtkObject->GetShaftRadius();
        }

        auto ArrowSource::setInvert(bool invert) -> void {
            this->m_vtkObject->SetInvert(invert);
            emit this->invertChanged();
            this->update();
        }

        auto ArrowSource::getInvert() -> bool {
            return this->m_vtkObject->GetInvert();
        }
    }
}
