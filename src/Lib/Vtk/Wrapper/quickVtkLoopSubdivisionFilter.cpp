#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register(true);

        LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New()) {
        }
    }
}
