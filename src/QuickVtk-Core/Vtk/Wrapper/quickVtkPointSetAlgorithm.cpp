#include "quickVtkPointSetAlgorithm.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<PointSetAlgorithm> PointSetAlgorithm::Register(true);

    PointSetAlgorithm::PointSetAlgorithm(vtkSmartPointer<vtkPointSetAlgorithm> vtkObject) : Algorithm(vtkObject) {
    }
}
