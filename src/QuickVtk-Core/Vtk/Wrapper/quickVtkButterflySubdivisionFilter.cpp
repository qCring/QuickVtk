#include "quickVtkButterflySubdivisionFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<ButterflySubdivisionFilter> ButterflySubdivisionFilter::Register(true);

    ButterflySubdivisionFilter::ButterflySubdivisionFilter() : InterpolatingSubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>::New()) {
    }
}
