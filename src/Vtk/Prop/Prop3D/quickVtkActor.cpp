#include "quickVtkActor.hpp"
#include "quickVtkMapper.hpp"
#include "quickVtkProperty.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Actor> Actor::Register;

        Actor::Actor() : Prop3D(vtkSmartPointer<vtkActor>::New()) {
            this->m_vtkObject = vtkActor::SafeDownCast(Prop::getVtkObject());
            this->m_property = new Property(this);
        }

        Actor::Actor(vtkSmartPointer<vtkActor> vtkObject) : Prop3D(vtkObject) {
            this->m_vtkObject = vtkObject;
            this->m_property = new Property(this);
        }

        auto Actor::getVtkObject() -> vtkSmartPointer<vtkActor> {
            return this->m_vtkObject;
        }

        auto Actor::getProperty() -> Property* {
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
            delete this->m_property;
        }
    }
}