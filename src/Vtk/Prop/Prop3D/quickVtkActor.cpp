#include "quickVtkActor.hpp"
#include "quickVtkMapper.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Actor> Actor::Register;

        Actor::Actor() : Prop3D(this) {
            this->setVtkActor(vtkSmartPointer<vtkActor>::New());
            this->m_mapper      = nullptr;
        }

        Actor::Actor(Actor* other) : Prop3D(this) {
            this->m_mapper      = nullptr;
        }

        auto Actor::setVtkActor(vtkSmartPointer<vtkActor> vtkActor) -> void {
            this->m_vtkActor = vtkActor;
            Prop3D::setVtkProp3D(vtkActor);
        }

        auto Actor::setMapper(Mapper* mapper) -> void {
            this->m_mapper = mapper;
            this->m_vtkActor->SetMapper(mapper->getVtkMapper());
            mapper->setProp(this);

            emit this->mapperChanged();

            this->update();
        }

        auto Actor::getMapper() -> Mapper* {
            return this->m_mapper;
        }

        auto Actor::getVtkActor() -> vtkSmartPointer<vtkActor> {
            return this->m_vtkActor;
        }

        Actor::~Actor() {
            this->m_vtkActor    = 0;
        }
    }
}