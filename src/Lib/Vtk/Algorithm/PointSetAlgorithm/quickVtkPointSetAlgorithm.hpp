#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkPointSetAlgorithm.h>

namespace quick {

    namespace Vtk {

        class PointSetAlgorithm : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::Symbol::AbstractClass<PointSetAlgorithm> Register;
        public:
            PointSetAlgorithm(vtkSmartPointer<vtkPointSetAlgorithm>);
        };
    }
}
