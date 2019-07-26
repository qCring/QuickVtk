#include "quickVtkPointSetAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<PointSetAlgorithm> PointSetAlgorithm::Register;

        PointSetAlgorithm::PointSetAlgorithm(vtkSmartPointer<vtkPointSetAlgorithm> vtkObject) : Algorithm(vtkObject) {
        }
    }
}
