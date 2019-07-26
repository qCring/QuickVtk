#include "quickVtkButterflySubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Symbol::Class<ButterflySubdivisionFilter> ButterflySubdivisionFilter::Register;

        ButterflySubdivisionFilter::ButterflySubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>::New()) {
        }
    }
}
