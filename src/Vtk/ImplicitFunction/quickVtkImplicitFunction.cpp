#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImplicitFunction> ImplicitFunction::Register;

        ImplicitFunction::ImplicitFunction(vtkSmartPointer<vtkImplicitFunction> vtkObject) : m_vtkObject(vtkObject) {
        }

        auto ImplicitFunction::update() -> void {
            for (auto callback : this->m_callbacks) {
                callback->operator()();
            }
        }

        auto ImplicitFunction::addCallback(cb_t&& callback) -> void {
            if (this->m_callbacks.contains(&callback)) {
                return;
            }

            this->m_callbacks.append(&callback);
        }

        auto ImplicitFunction::removeCallback(cb_t&& callback) -> void {
            this->m_callbacks.removeOne(&callback);
        }

        auto ImplicitFunction::getVtkObject() -> vtkSmartPointer<vtkImplicitFunction> {
            return this->m_vtkObject;
        }

        ImplicitFunction::~ImplicitFunction() {
        }
    }
}