#include "quickVtkThreadedImageAlgorithm.hpp"

namespace quick::Vtk {

    Qml::Register::AbstractClass<ThreadedImageAlgorithm> ThreadedImageAlgorithm::Register(true);

    ThreadedImageAlgorithm::ThreadedImageAlgorithm(vtkSmartPointer<vtkThreadedImageAlgorithm> vtkObject) : ImageAlgorithm(vtkObject) {
    }
}
