#pragma once

#include "quickVtkInterpolatingSubdivisionFilter.hpp"

#include <vtkLinearSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class LinearSubdivisionFilter : public InterpolatingSubdivisionFilter {
            Q_OBJECT
        private:
            static Qml::Register::Class<LinearSubdivisionFilter> Register;
        public:
            LinearSubdivisionFilter();
        };
    }
}
