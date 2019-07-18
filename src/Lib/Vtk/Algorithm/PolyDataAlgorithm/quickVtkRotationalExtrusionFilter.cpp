#include "quickVtkRotationalExtrusionFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<RotationalExtrusionFilter> RotationalExtrusionFilter::Register;

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

        auto RotationalExtrusionFilter::setAngle(float angle) -> void {
            this->m_vtkObject->SetAngle(angle);
            emit this->angleChanged();
            this->update();
        }

        auto RotationalExtrusionFilter::getAngle() -> float {
            return this->m_vtkObject->GetAngle();
        }

        auto RotationalExtrusionFilter::setTranslation(float translation) -> void {
            this->m_vtkObject->SetTranslation(translation);
            emit this->translationChanged();
            this->update();
        }

        auto RotationalExtrusionFilter::getTranslation() -> float {
            return this->m_vtkObject->GetTranslation();
        }

        auto RotationalExtrusionFilter::setDeltaRadius(float deltaRadius) -> void {
            this->m_vtkObject->SetDeltaRadius(deltaRadius);
            emit this->deltaRadiusChanged();
            this->update();
        }

        auto RotationalExtrusionFilter::getDeltaRadius() -> float {
            return this->m_vtkObject->GetDeltaRadius();
        }
    }
}
