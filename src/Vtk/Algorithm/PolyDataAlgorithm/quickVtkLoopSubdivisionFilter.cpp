#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register;

        LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New()) {
        }
    }
}