#include "quickVtkActor2D.hpp"
#include "quickVtkMapper2D.hpp"
#include "quickVtkProperty2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Actor2D> Actor2D::Register;

        Actor2D::Actor2D() : Prop(vtkSmartPointer<vtkActor2D>::New()) {
            this->m_vtkObject = vtkActor2D::SafeDownCast(Prop::getVtkObject());
        }

        Actor2D::Actor2D(vtkSmartPointer<vtkActor2D> vtkObject) : Prop(vtkObject) {
            this->m_vtkObject = vtkActor2D::SafeDownCast(vtkObject);
        }

        auto Actor2D::getVtkObject() -> vtkSmartPointer<vtkActor2D> {
            return vtkActor2D::SafeDownCast(Prop::getVtkObject());
        }

        auto Actor2D::setMapper2D(Mapper2D* mapper2D) -> void {
            this->m_mapper2D = mapper2D;
            this->m_vtkObject->SetMapper(mapper2D->getVtkObject());
            mapper2D->setProp(this);

            emit this->mapper2DChanged();

            this->update();
        }

        auto Actor2D::getMapper2D() -> Mapper2D* {
            return this->m_mapper2D;
        }

        auto Actor2D::setProperty2D(Property2D* property2D) -> void {
            if (this->m_property2D) {
                delete this->m_property2D;
                this->m_property2D = nullptr;
            }

            this->m_property2D = property2D;
        }

        auto Actor2D::getProperty2D() -> Property2D* {
            if (!this->m_property2D) {
                this->m_property2D = new Property2D(this);
            }

            return this->m_property2D;
        }

        auto Actor2D::setWidth(double width) -> void {
            this->m_vtkObject->SetWidth(width);
            emit this->widthChanged();
            this->update();
        }

        auto Actor2D::getWidth() -> double {
            return this->m_vtkObject->GetWidth();
        }

        auto Actor2D::setHeight(double height) -> void {
            this->m_vtkObject->SetHeight(height);
            emit this->heightChanged();
            this->update();
        }

        auto Actor2D::getHeight() -> double {
            return this->m_vtkObject->GetHeight();
        }

        Actor2D::~Actor2D() {
        }
    }
}