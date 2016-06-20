#include "quickVtkApproximatingSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::AbstractClass<ApproximatingSubdivisionFilter> ApproximatingSubdivisionFilter::Register;

        ApproximatingSubdivisionFilter::ApproximatingSubdivisionFilter() : PolyDataAlgorithm(this) {
            this->m_vtkApproximatingSubdivisionFilter = 0;
        }

        ApproximatingSubdivisionFilter::ApproximatingSubdivisionFilter(ApproximatingSubdivisionFilter* other) : PolyDataAlgorithm(this) {
        }

        auto ApproximatingSubdivisionFilter::setVtkApproximatingSubdivisionFilter(vtkSmartPointer<vtkApproximatingSubdivisionFilter>vtkApproximatingSubdivisionFilter) -> void {
            this->m_vtkApproximatingSubdivisionFilter = vtkApproximatingSubdivisionFilter;
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(vtkApproximatingSubdivisionFilter);
        }

        auto ApproximatingSubdivisionFilter::getVtkApproximatingSubdivisionFilter() -> vtkSmartPointer<vtkApproximatingSubdivisionFilter> {
            return this->m_vtkApproximatingSubdivisionFilter;
        }

        auto ApproximatingSubdivisionFilter::setNumberOfSubdivisions(int subdivisions) -> void {
            this->m_vtkApproximatingSubdivisionFilter->SetNumberOfSubdivisions(subdivisions);
            emit this->numberOfSubdivisionsChanged();
            this->update();
        }

        auto ApproximatingSubdivisionFilter::getNumberOfSubdivisions() -> int {
            return this->m_vtkApproximatingSubdivisionFilter->GetNumberOfSubdivisions();
        }

        ApproximatingSubdivisionFilter::~ApproximatingSubdivisionFilter() {
            this->m_vtkApproximatingSubdivisionFilter = 0;
        }
    }
}