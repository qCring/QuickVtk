#include "quickVtkDataSetAlgorithm.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<DataSetAlgorithm> DataSetAlgorithm::Register(true);

    DataSetAlgorithm::DataSetAlgorithm(vtkSmartPointer<vtkDataSetAlgorithm> vtkObject) : Algorithm(vtkObject) {
    }
}
