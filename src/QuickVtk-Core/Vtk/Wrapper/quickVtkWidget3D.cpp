#include "quickVtkWidget3D.hpp"

#include "quickVtkProp3D.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<Widget3D> Widget3D::Register(true);
    
    Widget3D::Widget3D(vtkSmartPointer<vtk3DWidget> vtkObject) : InteractorObserver(vtkObject) {
        this->m_vtkObject = vtk3DWidget::SafeDownCast(vtkObject);
    }
    
    auto Widget3D::getVtkObject() -> vtkSmartPointer<vtk3DWidget> {
        return this->m_vtkObject;
    }
    
    auto Widget3D::setProp3D(Prop3D* prop3D) -> void {
        this->m_prop3D = prop3D;
        emit this->prop3DChanged();
        
        if (prop3D != nullptr) {
            this->m_vtkObject->SetProp3D(prop3D->getVtkObject());
            this->m_vtkObject->PlaceWidget();
        }
    }
    
    auto Widget3D::getProp3D() -> Prop3D* {
        return this->m_prop3D;
    }
    
    auto Widget3D::setPlaceFactor(qreal placeFactor) -> void {
        this->m_vtkObject->SetPlaceFactor(placeFactor);
        emit this->placeFactorChanged();
    }
    
    auto Widget3D::getPlaceFactor() -> qreal {
        return this->m_vtkObject->GetPlaceFactor();
    }
    
    auto Widget3D::setHandleSize(qreal handleSize) -> void {
        this->m_vtkObject->SetHandleSize(handleSize);
        emit this->handleSizeChanged();
    }
    
    auto Widget3D::getHandleSize() -> qreal {
        return this->m_vtkObject->GetHandleSize();
    }
}
