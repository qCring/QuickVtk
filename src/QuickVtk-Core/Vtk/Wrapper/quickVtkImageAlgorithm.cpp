#include "quickVtkImageAlgorithm.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<ImageAlgorithm> ImageAlgorithm::Register(true);

    ImageAlgorithm::ImageAlgorithm(vtkSmartPointer<vtkImageAlgorithm> vtkObject) : Algorithm(vtkObject) {
    }
}
