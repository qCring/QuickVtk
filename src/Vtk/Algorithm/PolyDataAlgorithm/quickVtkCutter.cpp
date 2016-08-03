#include "quickVtkCutter.hpp"

#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Cutter> Cutter::Register;

        Cutter::Cutter() : PolyDataAlgorithm(vtkSmartPointer<vtkCutter>::New()) {
            this->m_vtkObject = vtkCutter::SafeDownCast(Algorithm::getVtkObject());
            this->m_cutFunctionCb = [this] () {
                this->updateCutFunction();
            };
        }

        auto Cutter::updateCutFunction() -> void {
            if (this->m_cutFunction) {
                this->update();
            }
        }

        auto Cutter::setCutFunction(ImplicitFunction* cutFunction) -> void {
            if (this->m_cutFunction) {
                this->m_cutFunction->removeCallback(std::move(this->m_cutFunctionCb));
            }

            this->m_cutFunction = cutFunction;

            if (cutFunction) {
                this->m_vtkObject->SetCutFunction(cutFunction->getVtkObject());
                cutFunction->addCallback(std::move(this->m_cutFunctionCb));
                this->updateCutFunction();
            }

            emit this->cutFunctionChanged();
        }

        auto Cutter::getCutFunction() -> ImplicitFunction* {
            return this->m_cutFunction;
        }

        Cutter::~Cutter() {
            if (this->m_cutFunction) {
                this->m_cutFunction->removeCallback(std::move(this->m_cutFunctionCb));
            }
        }
    }
}
