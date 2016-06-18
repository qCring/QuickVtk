#include "quickVtkArrowSource.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<ArrowSource> ArrowSource::Register;

        ArrowSource::ArrowSource() : PolyDataAlgorithm(this) {
            this->m_vtkArrowSource = vtkSmartPointer<vtkArrowSource>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkArrowSource);
        }

        auto ArrowSource::setTipResolution(int tipResolution) -> void {
            this->m_vtkArrowSource->SetTipResolution(tipResolution);
            emit this->tipResolutionChanged();
            this->update();
        }

        auto ArrowSource::getTipResolution() -> int {
            return this->m_vtkArrowSource->GetTipResolution();
        }

        auto ArrowSource::setTipLength(double tipLength) -> void {
            this->m_vtkArrowSource->SetTipLength(tipLength);
            emit this->tipLengthChanged();
            this->update();
        }

        auto ArrowSource::getTipLength() -> double {
            return this->m_vtkArrowSource->GetTipLength();
        }

        auto ArrowSource::setTipRadius(double tipRadius) -> void {
            this->m_vtkArrowSource->SetTipRadius(tipRadius);
            emit this->tipRadiusChanged();
            this->update();
        }

        auto ArrowSource::getTipRadius() -> double {
            return this->m_vtkArrowSource->GetTipRadius();
        }

        auto ArrowSource::setShaftResolution(int shaftResolution) -> void {
            this->m_vtkArrowSource->SetShaftResolution(shaftResolution);
            emit this->shaftResolutionChanged();
            this->update();
        }

        auto ArrowSource::getShaftResolution() -> int {
            return this->m_vtkArrowSource->GetShaftResolution();
        }

        auto ArrowSource::setShaftRadius(double shaftRadius) -> void {
            this->m_vtkArrowSource->SetShaftRadius(shaftRadius);
            emit this->shaftRadiusChanged();
            this->update();
        }

        auto ArrowSource::getShaftRadius() -> double {
            return this->m_vtkArrowSource->GetShaftRadius();
        }

        auto ArrowSource::setInvert(bool invert) -> void {
            this->m_vtkArrowSource->SetInvert(invert);
            emit this->invertChanged();
            this->update();
        }

        auto ArrowSource::getInvert() -> bool {
            return this->m_vtkArrowSource->GetInvert();
        }

        ArrowSource::~ArrowSource() {
            this->m_vtkArrowSource = nullptr;
        }
    }
}