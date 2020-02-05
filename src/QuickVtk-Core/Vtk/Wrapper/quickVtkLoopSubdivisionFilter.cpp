#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register(true);

    LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New()) {
    }
}
