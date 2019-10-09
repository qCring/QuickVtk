#include "quickVtkProperty2D.hpp"
#include "quickVtkActor2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::UncreatableClass<Property2D> Property2D::Register(true);

        Property2D::Property2D(Actor2D* actor2D) : m_actor2D(actor2D), m_vtkActor2D(actor2D->getVtkObject()) {
        }

        auto Property2D::update() -> void {
            this->m_actor2D->update();
        }

        auto Property2D::setColor(const QColor& color) -> void {
            this->m_color = color;

            this->m_vtkActor2D->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());
            this->update();

            emit this->colorChanged();
        }

        auto Property2D::getColor() -> QColor {
            return this->m_color;
        }

        auto Property2D::setOpacity(qreal opacity) -> void {
            this->m_vtkActor2D->GetProperty()->SetOpacity(opacity);
            this->update();

            emit this->opacityChanged();
        }

        auto Property2D::getOpacity() -> qreal {
            return this->m_vtkActor2D->GetProperty()->GetOpacity();
        }
    }
}
