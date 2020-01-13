#include "quickVtkProp.hpp"
#include "quickVtkViewer.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<Prop> Prop::Register(true);

        Prop::Prop(vtkSmartPointer<vtkProp> vtkObject) : Object(Object::Type::Prop), m_vtkObject(vtkObject) {
        }

        auto Prop::getVtkObject() -> vtkSmartPointer<vtkProp> {
            return this->m_vtkObject;
        }

        auto Prop::linkViewer(Viewer* viewer) -> void {
            this->m_viewers.append(viewer);
            this->m_initialized = true;
        }

        auto Prop::unlinkViewer(Viewer* viewer) -> void {
            this->m_viewers.removeOne(viewer);
        }

        auto Prop::update() -> void {
            if (!this->m_initialized) {
                return;
            }

            for (auto v : this->m_viewers) {
                v->update();
            }
        }

        auto Prop::setVisibility(bool visible) -> void {
            this->m_vtkObject->SetVisibility(visible);
            emit this->visibilityChanged();
            update();
        }

        auto Prop::getVisibility() -> bool {
            return this->m_vtkObject->GetVisibility();
        }
        
        Prop::~Prop() {
            this->m_initialized = false;
            this->m_vtkObject = nullptr;
        }
    }
}
