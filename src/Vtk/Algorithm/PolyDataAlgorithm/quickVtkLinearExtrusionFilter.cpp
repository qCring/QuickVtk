#include "quickVtkLinearExtrusionFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<LinearExtrusionFilter> LinearExtrusionFilter::Register;

        LinearExtrusionFilter::LinearExtrusionFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkLinearExtrusionFilter>::New()) {
            this->m_vtkObject = vtkLinearExtrusionFilter::SafeDownCast(Algorithm::getVtkObject());

            this->m_vector = new Math::Vector3([this](){
                this->m_vtkObject->SetVector(this->m_vector->getValues().data());
                this->update();
            });

            this->m_extrusionPoint = new Math::Vector3([this](){
                this->m_vtkObject->SetExtrusionPoint(this->m_extrusionPoint->getValues().data());
                this->update();
            });
        }

        auto LinearExtrusionFilter::setExtrusionType(ExtrusionType extrusionType) -> void {
            this->m_vtkObject->SetExtrusionType(extrusionType);
            emit this->extrusionTypeChanged();
            this->update();
        }

        auto LinearExtrusionFilter::getExtrusionType() -> ExtrusionType {
            return (ExtrusionType) this->m_vtkObject->GetExtrusionType();
        }

        auto LinearExtrusionFilter::setScaleFactor(float scaleFactor) -> void {
            this->m_vtkObject->SetScaleFactor(scaleFactor);
            emit this->scaleFactorChanged();
            this->update();
        }

        auto LinearExtrusionFilter::getScaleFactor() -> float {
            return this->m_vtkObject->GetScaleFactor();
        }

        auto LinearExtrusionFilter::setCapping(bool capping) -> void {
            this->m_vtkObject->SetCapping(capping);
            emit this->cappingChanged();
            this->update();
        }

        auto LinearExtrusionFilter::getCapping() -> bool {
            return this->m_vtkObject->GetCapping();
        }
        
        auto LinearExtrusionFilter::getVector() -> Math::Vector3* {
            return this->m_vector;
        }

        auto LinearExtrusionFilter::getExtrusionPoint() -> Math::Vector3* {
            return this->m_extrusionPoint;
        }
    }
}
