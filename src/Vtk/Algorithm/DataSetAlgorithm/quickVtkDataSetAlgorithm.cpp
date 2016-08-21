#include "quickVtkDataSetAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<DataSetAlgorithm> DataSetAlgorithm::Register;

        DataSetAlgorithm::DataSetAlgorithm(vtkSmartPointer<vtkDataSetAlgorithm> vtkObject) : Algorithm(vtkObject) {
        }
    }
}