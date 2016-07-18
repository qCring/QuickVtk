#include "quickVtkActor2D.hpp"
#include "quickVtkMapper2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Actor2D> Actor2D::Register;

        Actor2D::Actor2D() : Prop(this) {
            this->m_mapper2D = nullptr;
            setVtkActor2D(vtkSmartPointer<vtkActor2D>::New());
        }

        Actor2D::Actor2D(Actor2D* other) : Prop(this) {
        }

        auto Actor2D::setMapper(Mapper2D* mapper2D) -> void {
            this->m_mapper2D = mapper2D;
            this->m_vtkActor2D->SetMapper(mapper2D->getVtkMapper2D());
            mapper2D->setProp(this);

            emit this->mapperChanged();

            this->update();
        }

        auto Actor2D::getMapper() -> Mapper2D* {
            return this->m_mapper2D;
        }

        auto Actor2D::setVtkActor2D(vtkSmartPointer<vtkActor2D> vtkActor2D) -> void {
            this->m_vtkActor2D = vtkActor2D;
            Prop::setVtkProp(vtkActor2D);
        }

        auto Actor2D::getVtkActor2D() -> vtkSmartPointer<vtkActor2D> {
            return this->m_vtkActor2D;
        }

        Actor2D::~Actor2D() {
        }
    }
}