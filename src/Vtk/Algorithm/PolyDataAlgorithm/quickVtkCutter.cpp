#include "quickVtkCutter.hpp"

#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Cutter> Cutter::Register;

        Cutter::Cutter() : PolyDataAlgorithm(this) {
            this->m_vtkCutter       = vtkSmartPointer<vtkCutter>::New();
            this->m_cutFunction     = 0;

            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkCutter);
        }

        Cutter::Cutter(Cutter* other) : PolyDataAlgorithm(this) {
        }

        auto Cutter::setCutFunction(ImplicitFunction* cutFunction) -> void {
            this->m_cutFunction = cutFunction;
            this->m_vtkCutter->SetCutFunction(cutFunction->getVtkImplicitFunction());

            emit this->cutFunctionChanged();
        }

        auto Cutter::getCutFunction() -> ImplicitFunction* {
            return this->m_cutFunction;
        }

        Cutter::~Cutter() {
            this->m_vtkCutter = 0;
        }
    }
}
