#include "quickVtkActor2D.hpp"
#include "quickVtkMapper2D.hpp"
#include "quickVtkProperty2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<Actor2D> Actor2D::Register(true);

        Actor2D::Actor2D() : Prop(vtkSmartPointer<vtkActor2D>::New()) {
            this->m_vtkObject = vtkActor2D::SafeDownCast(Prop::getVtkObject());
            this->m_property = new Property2D(this);
        }

        Actor2D::Actor2D(vtkSmartPointer<vtkActor2D> vtkObject) : Prop(vtkObject) {
            this->m_vtkObject = vtkActor2D::SafeDownCast(vtkObject);
            this->m_property = new Property2D(this);
        }

        auto Actor2D::getVtkObject() -> vtkSmartPointer<vtkActor2D> {
            return vtkActor2D::SafeDownCast(Prop::getVtkObject());
        }

        auto Actor2D::setMapper(Mapper2D* mapper) -> void {
            this->m_mapper = mapper;
            this->m_vtkObject->SetMapper(mapper->getVtkObject());
            mapper->setProp(this);

            emit this->mapperChanged();

            this->update();
        }

        auto Actor2D::getMapper() -> Mapper2D* {
            return this->m_mapper;
        }

        auto Actor2D::getProperty() -> Property2D* {
            return this->m_property;
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
            delete this->m_property;
        }
    }
}
