#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkPolyDataAlgorithm.h>

namespace quick {

    namespace Vtk {

        class PolyDataAlgorithm : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<PolyDataAlgorithm> Register;
        public:
            PolyDataAlgorithm(vtkSmartPointer<vtkPolyDataAlgorithm>);
        };
    }
}