#include "quickVtkPointWidget.hpp"
#include <vtkProperty.h>

namespace quick::Vtk {

    Qml::Register::Class<PointWidget> PointWidget::Register(true);

    PointWidget::PointWidget() : Widget3D(vtkSmartPointer<vtkPointWidget>::New()) {
        this->m_vtkObject = vtkPointWidget::SafeDownCast(Widget3D::getVtkObject());
    }
    
    auto PointWidget::setTranslationMode(bool translationMode) -> void {
        this->m_vtkObject->SetTranslationMode(translationMode);
        emit this->translationModeChanged();
    }
    
    auto PointWidget::getTranslationMode() -> bool {
        return this->m_vtkObject->GetTranslationMode();
    }
    
    auto PointWidget::setOutline(bool outline) -> void {
        this->m_vtkObject->SetOutline(outline);
        emit this->outlineChanged();
    }
    
    auto PointWidget::getOutline() -> bool {
        return this->m_vtkObject->GetOutline();
    }
}
