#pragma once

#include "quickVtkApproximatingSubdivisionFilter.hpp"

#include <vtkLoopSubdivisionFilter.h>

namespace quick::Vtk {

    class LoopSubdivisionFilter : public ApproximatingSubdivisionFilter {
        Q_OBJECT
    private:
        static Qml::Register::Class<LoopSubdivisionFilter> Register;
    public:
        LoopSubdivisionFilter();
    };
}
