#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkAbstractClass<ImplicitFunction> ImplicitFunction::Register;

        ImplicitFunction::ImplicitFunction() {
        }

        ImplicitFunction::ImplicitFunction(ImplicitFunction* other) {
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