#include "quickVtkAbstractWidget.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::AbstractClass<AbstractWidget> AbstractWidget::Register(true);

        AbstractWidget::AbstractWidget(vtkSmartPointer<vtkAbstractWidget> vtkObject) : Object(Object::Type::Widget), m_vtkObject(vtkObject) {
        }

        auto AbstractWidget::getVtkObject() -> vtkSmartPointer<vtkAbstractWidget> {
            return this->m_vtkObject;
        }

        auto AbstractWidget::setEnabled(bool enabled) -> void {
            this->m_vtkObject->SetEnabled(enabled);
            emit this->enabledChanged();
        }

        auto AbstractWidget::getEnabled() -> bool {
            return this->m_vtkObject->GetEnabled();
        }
    }
}
