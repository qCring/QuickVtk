#pragma once

#include "quickVtkInterpolatingSubdivisionFilter.hpp"

#include <vtkButterflySubdivisionFilter.h>

namespace quick {
    namespace Vtk {

        class ButterflySubdivisionFilter : public InterpolatingSubdivisionFilter {
            Q_OBJECT
        private:
            static Qml::Register::Class<ButterflySubdivisionFilter> Register;
        public:
            ButterflySubdivisionFilter();
        };
    }
}
