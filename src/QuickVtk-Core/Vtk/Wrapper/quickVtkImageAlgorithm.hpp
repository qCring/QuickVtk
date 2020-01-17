#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkImageAlgorithm.h>

namespace quick {
    namespace Vtk {

        class ImageAlgorithm : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<ImageAlgorithm> Register;
        public:
            ImageAlgorithm(vtkSmartPointer<vtkImageAlgorithm>);
        };
    }
}
