#include "quickVtkButterflySubdivisionFilter.hpp"

namespace quick {
    namespace Vtk {
        Qml::Register::Class<ButterflySubdivisionFilter> ButterflySubdivisionFilter::Register(true);

        ButterflySubdivisionFilter::ButterflySubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>::New()) {
        }
    }
}
