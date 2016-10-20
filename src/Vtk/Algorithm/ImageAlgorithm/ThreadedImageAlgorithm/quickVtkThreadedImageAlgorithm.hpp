#pragma once

#include "quickVtkImageAlgorithm.hpp"

#include <vtkThreadedImageAlgorithm.h>

namespace quick {

    namespace Vtk {

        class ThreadedImageAlgorithm : public ImageAlgorithm {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::AbstractClass<ThreadedImageAlgorithm> Register;
        public:
            ThreadedImageAlgorithm(vtkSmartPointer<vtkThreadedImageAlgorithm>);
        };
    }
}
