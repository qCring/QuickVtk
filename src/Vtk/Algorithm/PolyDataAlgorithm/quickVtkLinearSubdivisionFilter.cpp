#include "quickVtkLinearSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<LinearSubdivisionFilter> LinearSubdivisionFilter::Register;

        LinearSubdivisionFilter::LinearSubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkLinearSubdivisionFilter>::New()) {
        }
    }
}
