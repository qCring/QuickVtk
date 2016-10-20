#pragma once

#include "quickVtkThreadedImageAlgorithm.hpp"

#include <vtkImageLaplacian.h>

namespace quick {

    namespace Vtk {

        class ImageLaplacian : public ThreadedImageAlgorithm {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::Class<ImageLaplacian> Register;
        public:
            ImageLaplacian();
        };
    }
}
