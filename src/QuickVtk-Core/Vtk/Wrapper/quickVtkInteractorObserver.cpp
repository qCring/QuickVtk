#include "quickVtkInteractorObserver.hpp"

namespace quick::Vtk {
    
    Qml::Register::AbstractClass<InteractorObserver> InteractorObserver::Register(true);
    
    InteractorObserver::InteractorObserver(vtkSmartPointer<vtkInteractorObserver> vtkObject) : Object(Object::Type::InteractorObserver), m_vtkObject(vtkObject) {
    }
    
    auto InteractorObserver::getVtkObject() -> vtkSmartPointer<vtkInteractorObserver> {
        return this->m_vtkObject;
    }
    
    auto InteractorObserver::setInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor) -> void {
        this->m_interactor = interactor;
        
        this->m_vtkObject->SetInteractor(interactor);
        this->m_vtkObject->SetEnabled(this->m_enabled);
    }
    
    auto InteractorObserver::setEnabled(bool enabled) -> void {
        this->m_enabled = enabled;
        emit this->enabledChanged();
        
        if (this->m_interactor != nullptr) {
            this->m_vtkObject->SetEnabled(enabled);
        }
    }
    
    auto InteractorObserver::getEnabled() -> bool {
        return this->m_enabled;
    }
}
