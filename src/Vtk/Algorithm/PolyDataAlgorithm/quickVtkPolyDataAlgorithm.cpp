#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<PolyDataAlgorithm> PolyDataAlgorithm::Register;

        PolyDataAlgorithm::PolyDataAlgorithm(vtkSmartPointer<vtkPolyDataAlgorithm> vtkObject) : Algorithm(vtkObject) {
        }
    }
}
