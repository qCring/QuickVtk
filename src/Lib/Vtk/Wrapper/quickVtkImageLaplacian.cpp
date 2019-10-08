#include "quickVtkImageLaplacian.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<ImageLaplacian> ImageLaplacian::Register(true);

        ImageLaplacian::ImageLaplacian() : ThreadedImageAlgorithm(vtkSmartPointer<vtkImageLaplacian>::New()) {
        }
    }
}
