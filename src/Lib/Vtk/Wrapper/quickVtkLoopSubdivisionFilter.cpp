#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register(true);

        LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New()) {
        }
    }
}
