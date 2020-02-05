#include "quickVtkRotationalExtrusionFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<RotationalExtrusionFilter> RotationalExtrusionFilter::Register(true);

    RotationalExtrusionFilter::RotationalExtrusionFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkRotationalExtrusionFilter>::New()) {
        this->m_vtkObject = vtkRotationalExtrusionFilter::SafeDownCast(Algorithm::getVtkObject());
    }

    auto RotationalExtrusionFilter::setResolution(int resolution) -> void {
        this->m_vtkObject->SetResolution(resolution);
        emit this->resolutionChanged();
        this->update();
    }

    auto RotationalExtrusionFilter::getResolution() -> int {
        return this->m_vtkObject->GetResolution();
    }

    auto RotationalExtrusionFilter::setCapping(bool capping) -> void {
        this->m_vtkObject->SetCapping(capping);
        emit this->cappingChanged();
        this->update();
    }

    auto RotationalExtrusionFilter::getCapping() -> bool {
        return this->m_vtkObject->GetCapping();
    }

    auto RotationalExtrusionFilter::setAngle(qreal angle) -> void {
        this->m_vtkObject->SetAngle(angle);
        emit this->angleChanged();
        this->update();
    }

    auto RotationalExtrusionFilter::getAngle() -> qreal {
        return this->m_vtkObject->GetAngle();
    }

    auto RotationalExtrusionFilter::setTranslation(qreal translation) -> void {
        this->m_vtkObject->SetTranslation(translation);
        emit this->translationChanged();
        this->update();
    }

    auto RotationalExtrusionFilter::getTranslation() -> qreal {
        return this->m_vtkObject->GetTranslation();
    }

    auto RotationalExtrusionFilter::setDeltaRadius(qreal deltaRadius) -> void {
        this->m_vtkObject->SetDeltaRadius(deltaRadius);
        emit this->deltaRadiusChanged();
        this->update();
    }

    auto RotationalExtrusionFilter::getDeltaRadius() -> qreal {
        return this->m_vtkObject->GetDeltaRadius();
    }
}
