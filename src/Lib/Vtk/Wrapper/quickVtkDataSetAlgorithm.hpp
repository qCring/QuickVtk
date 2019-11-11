#pragma once

#include "quickVtkAlgorithm.hpp"

#include <vtkDataSetAlgorithm.h>

namespace quick {

    namespace Vtk {

        class DataSetAlgorithm : public Algorithm {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<DataSetAlgorithm> Register;
        public:
            DataSetAlgorithm(vtkSmartPointer<vtkDataSetAlgorithm>);
        };
    }
}
