#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::VtkAbstractClass<PolyDataAlgorithm> PolyDataAlgorithm::Register;

        PolyDataAlgorithm::PolyDataAlgorithm() : Algorithm(this) {
            this->m_vtkPolyDataAlgorithm    = 0;
        }

        PolyDataAlgorithm::PolyDataAlgorithm(PolyDataAlgorithm* other) : Algorithm(this) {
        }

        auto PolyDataAlgorithm::setVtkPolyDataAlgorithm(vtkSmartPointer<vtkPolyDataAlgorithm> vtkPolyDataAlgorithm) -> void {
            this->m_vtkPolyDataAlgorithm = vtkPolyDataAlgorithm;
            Algorithm::setVtkAlgorithm(vtkPolyDataAlgorithm);
        }

        auto PolyDataAlgorithm::getVtkPolyDataAlgorithm() -> vtkSmartPointer<vtkPolyDataAlgorithm> {
            return this->m_vtkPolyDataAlgorithm;
        }

        PolyDataAlgorithm::~PolyDataAlgorithm() {
        }
    }
}