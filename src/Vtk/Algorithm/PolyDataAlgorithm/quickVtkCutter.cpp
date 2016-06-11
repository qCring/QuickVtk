#include "quickVtkCutter.hpp"

#include "quickVtkImplicitFunction.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkClass<Cutter> Cutter::Register;

        Cutter::Cutter() : PolyDataAlgorithm(this) {
            this->m_vtkCutter = vtkSmartPointer<vtkCutter>::New();

            this->m_cutFunctionCb = [this] () {
                this->updateCutFunction();
            };

            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkCutter);
        }

        Cutter::Cutter(Cutter* other) : PolyDataAlgorithm(this) {
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
                this->m_vtkCutter->SetCutFunction(cutFunction->getVtkImplicitFunction());
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
            
            this->m_vtkCutter = nullptr;
        }
    }
}
