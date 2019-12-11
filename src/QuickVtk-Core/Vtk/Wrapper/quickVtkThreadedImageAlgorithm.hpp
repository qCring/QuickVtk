#pragma once

#include "quickVtkImageAlgorithm.hpp"

#include <vtkThreadedImageAlgorithm.h>

namespace quick {

    namespace Vtk {

        class ThreadedImageAlgorithm : public ImageAlgorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<ThreadedImageAlgorithm> Register;
        public:
            ThreadedImageAlgorithm(vtkSmartPointer<vtkThreadedImageAlgorithm>);
        };
    }
}
