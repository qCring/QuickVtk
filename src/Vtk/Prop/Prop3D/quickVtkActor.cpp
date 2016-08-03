#include "quickVtkActor.hpp"
#include "quickVtkMapper.hpp"
#include "quickVtkProperty.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Actor> Actor::Register;

        Actor::Actor() : Prop3D(vtkSmartPointer<vtkActor>::New()) {
            this->m_vtkObject = vtkActor::SafeDownCast(Prop::getVtkObject());
        }

        Actor::Actor(vtkSmartPointer<vtkActor> vtkObject) : Prop3D(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto Actor::getVtkObject() -> vtkSmartPointer<vtkActor> {
            return this->m_vtkObject;
        }

        auto Actor::setProperty(Property* property) -> void {
            if (this->m_property) {
                delete this->m_property;
                this->m_property = nullptr;
            }

            this->m_property = property;
        }

        auto Actor::getProperty() -> Property* {
            if (!this->m_property) {
                this->m_property = new Property(this);
            }

            return this->m_property;
        }

        auto Actor::setMapper(Mapper* mapper) -> void {
            this->m_mapper = mapper;
            this->m_vtkObject->SetMapper(mapper->getVtkObject());
            mapper->setProp(this);

            emit this->mapperChanged();

            this->update();
        }

        auto Actor::getMapper() -> Mapper* {
            return this->m_mapper;
        }

        Actor::~Actor() {
            // todo: delete mapper?
        }
    }
}