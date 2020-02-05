#include "quickVtkPolyDataAlgorithm.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<PolyDataAlgorithm> PolyDataAlgorithm::Register(true);

    PolyDataAlgorithm::PolyDataAlgorithm(vtkSmartPointer<vtkPolyDataAlgorithm> vtkObject) : Algorithm(vtkObject) {
    }
}
