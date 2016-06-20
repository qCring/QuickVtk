#include "quickVtkLinearSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<LinearSubdivisionFilter> LinearSubdivisionFilter::Register;

        LinearSubdivisionFilter::LinearSubdivisionFilter() : InterpolatingSubdivisionFilter(this) {
            this->setVtkLinearSubdivisionFilter(vtkSmartPointer<vtkLinearSubdivisionFilter>::New());
        }

        auto LinearSubdivisionFilter::setVtkLinearSubdivisionFilter(vtkSmartPointer<vtkLinearSubdivisionFilter> vtkLinearSubdivisionFilter) -> void {
            this->m_vtkLinearSubdivisionFilter = vtkLinearSubdivisionFilter;
            InterpolatingSubdivisionFilter::setVtkInterpolatingSubdivisionFilter(vtkLinearSubdivisionFilter);
        }

        auto LinearSubdivisionFilter::getVtkLinearSubdivisionFilter() -> vtkSmartPointer<vtkLinearSubdivisionFilter> {
            return this->m_vtkLinearSubdivisionFilter;
        }

        LinearSubdivisionFilter::~LinearSubdivisionFilter() {
            this->m_vtkLinearSubdivisionFilter = 0;
        }
    }
}