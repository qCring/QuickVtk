#include "quickVtkButterflySubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<ButterflySubdivisionFilter> ButterflySubdivisionFilter::Register;

        ButterflySubdivisionFilter::ButterflySubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>::New()) {
        }
    }
}