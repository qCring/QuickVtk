#include "quickVtkProp.hpp"
#include "quickVtkViewer.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<Prop> Prop::Register;

        Prop::Prop() {
            this->m_vtkProp = 0;
        }

        Prop::Prop(Prop* prop) {
        }

        auto Prop::setVtkProp(vtkSmartPointer<vtkProp> prop) -> void {
            this->m_vtkProp = prop;
        }

        auto Prop::getVtkProp() -> vtkSmartPointer<vtkProp> {
            return this->m_vtkProp;
        }

        auto Prop::linkViewer(Viewer* viewer) -> void {
            this->m_viewers.append(viewer);
            this->m_initialized = true;
        }

        auto Prop::unlinkViewer(Viewer* viewer) -> void {
            if (!this->m_viewers.removeOne(viewer)) {
                throw "leak";
            }
        }

        auto Prop::update() -> void {
            if (!this->m_initialized) {
                return;
            }

            for (auto v : this->m_viewers) {
                v->update();
            }
        }

        auto Prop::setVisible(bool visible) -> void {
            this->m_vtkProp->SetVisibility(visible);

            emit this->visibleChanged();

            update();
        }

        auto Prop::isVisible() -> bool {
            return this->m_vtkProp->GetVisibility();
        }

        Prop::~Prop() {
            /*
             if (this->m_renderView)
             {
             this->m_renderView->removeData(this);
             }*/
            this->m_initialized = false;
            this->m_vtkProp     = 0;
        }
    }
}