#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkAbstractClass<ImplicitFunction> ImplicitFunction::Register;

        ImplicitFunction::ImplicitFunction(ImplicitFunction* other) {
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

        auto ImplicitFunction::setVtkImplicitFunction(vtkSmartPointer<vtkImplicitFunction> vtkImplicitFunction) -> void {
            this->m_vtkImplicitFunction = vtkImplicitFunction;
        }

        auto ImplicitFunction::getVtkImplicitFunction() -> vtkSmartPointer<vtkImplicitFunction> {
            return this->m_vtkImplicitFunction;
        }

        ImplicitFunction::~ImplicitFunction() {
        }
    }
}