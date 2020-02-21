#include "quickVtkLineWidget.hpp"
#include <vtkProperty.h>

namespace quick::Vtk {

    Qml::Register::Class<LineWidget> LineWidget::Register(true);

    LineWidget::LineWidget() : Widget3D(vtkSmartPointer<vtkLineWidget>::New()) {
        this->m_point1 = new Math::Vector3({0, 0, 0});
        this->m_point2 = new Math::Vector3({0, 0, 0});
        
        this->m_vtkObject = vtkLineWidget::SafeDownCast(Widget3D::getVtkObject());
        this->m_vtkObject->AddObserver(vtkCommand::InteractionEvent, this, &LineWidget::ProcessInteractionEvent);
        
        this->m_point1->setFromVtkArray(this->m_vtkObject->GetPoint1());
        this->m_point2->setFromVtkArray(this->m_vtkObject->GetPoint2());
    }
    
    auto LineWidget::ProcessInteractionEvent(vtkObject*, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(callData)) -> void {
        this->m_point1->setFromVtkArray(this->m_vtkObject->GetPoint1());
        this->m_point2->setFromVtkArray(this->m_vtkObject->GetPoint2());
    }
    
    auto LineWidget::getPoint1() -> Math::Vector3* {
        return this->m_point1;
    }
    
    auto LineWidget::getPoint2() -> Math::Vector3* {
        return this->m_point2;
    }
}
