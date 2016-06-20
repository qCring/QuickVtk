#include "quickVtkButterflySubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<ButterflySubdivisionFilter> ButterflySubdivisionFilter::Register;

        ButterflySubdivisionFilter::ButterflySubdivisionFilter() : InterpolatingSubdivisionFilter(this) {
            this->setVtkButterflySubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>::New());
        }

        auto ButterflySubdivisionFilter::setVtkButterflySubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter> vtkButterflySubdivisionFilter) -> void {
            this->m_vtkButterflySubdivisionFilter = vtkButterflySubdivisionFilter;
            InterpolatingSubdivisionFilter::setVtkInterpolatingSubdivisionFilter(vtkButterflySubdivisionFilter);
        }

        auto ButterflySubdivisionFilter::getVtkButterflySubdivisionFilter() -> vtkSmartPointer<vtkButterflySubdivisionFilter> {
            return this->m_vtkButterflySubdivisionFilter;
        }

        ButterflySubdivisionFilter::~ButterflySubdivisionFilter() {
            this->m_vtkButterflySubdivisionFilter = nullptr;
        }
    }
}