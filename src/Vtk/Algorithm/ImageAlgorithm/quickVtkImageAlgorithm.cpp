#include "quickVtkImageAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ImageAlgorithm> ImageAlgorithm::Register;

        ImageAlgorithm::ImageAlgorithm(vtkSmartPointer<vtkImageAlgorithm> vtkObject) : Algorithm(vtkObject) {
        }
    }
}