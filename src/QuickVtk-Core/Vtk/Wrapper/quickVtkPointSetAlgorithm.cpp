#include "quickVtkPointSetAlgorithm.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::AbstractClass<PointSetAlgorithm> PointSetAlgorithm::Register(true);

        PointSetAlgorithm::PointSetAlgorithm(vtkSmartPointer<vtkPointSetAlgorithm> vtkObject) : Algorithm(vtkObject) {
        }
    }
}
