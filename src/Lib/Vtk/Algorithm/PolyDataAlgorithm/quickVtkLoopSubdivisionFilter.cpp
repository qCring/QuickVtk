#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register;

        LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New()) {
        }
    }
}
