#include "quickVtkLinearSubdivisionFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<LinearSubdivisionFilter> LinearSubdivisionFilter::Register(true);

    LinearSubdivisionFilter::LinearSubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkLinearSubdivisionFilter>::New()) {
    }
}
