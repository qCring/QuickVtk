#include "quickVtkThreadedImageAlgorithm.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<ThreadedImageAlgorithm> ThreadedImageAlgorithm::Register(true);

        ThreadedImageAlgorithm::ThreadedImageAlgorithm(vtkSmartPointer<vtkThreadedImageAlgorithm> vtkObject) : ImageAlgorithm(vtkObject) {
        }
    }
}
