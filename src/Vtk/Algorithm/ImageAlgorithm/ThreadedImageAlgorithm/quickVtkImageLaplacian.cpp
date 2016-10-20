#include "quickVtkImageLaplacian.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<ImageLaplacian> ImageLaplacian::Register;

        ImageLaplacian::ImageLaplacian() : ThreadedImageAlgorithm(vtkSmartPointer<vtkImageLaplacian>::New()) {
        }
    }
}
