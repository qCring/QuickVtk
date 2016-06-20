#include "quickVtkInterpolatingSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<InterpolatingSubdivisionFilter> InterpolatingSubdivisionFilter::Register;

        InterpolatingSubdivisionFilter::InterpolatingSubdivisionFilter() : PolyDataAlgorithm(this) {
            this->m_vtkInterpolatingSubdivisionFilter = nullptr;
        }

        InterpolatingSubdivisionFilter::InterpolatingSubdivisionFilter(InterpolatingSubdivisionFilter* other) : PolyDataAlgorithm(this) {
        }

        auto InterpolatingSubdivisionFilter::setVtkInterpolatingSubdivisionFilter(vtkSmartPointer<vtkInterpolatingSubdivisionFilter> vtkInterpolatingSubdivisionFilter) -> void {
            this->m_vtkInterpolatingSubdivisionFilter = vtkInterpolatingSubdivisionFilter;
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(vtkInterpolatingSubdivisionFilter);
        }

        auto InterpolatingSubdivisionFilter::setNumberOfSubdivisions(int value) -> void {
            this->m_vtkInterpolatingSubdivisionFilter->SetNumberOfSubdivisions(value);
            emit this->numberOfSubdivisionsChanged();
            this->update();
        }

        auto InterpolatingSubdivisionFilter::getNumberOfSubdivisions() -> int {
            return this->m_vtkInterpolatingSubdivisionFilter->GetNumberOfSubdivisions();
        }

        auto InterpolatingSubdivisionFilter::getVtkInterpolatingSubdivisionFilter() -> vtkSmartPointer<vtkInterpolatingSubdivisionFilter> {
            return this->m_vtkInterpolatingSubdivisionFilter;
        }

        InterpolatingSubdivisionFilter::~InterpolatingSubdivisionFilter() {
            this->m_vtkInterpolatingSubdivisionFilter = 0;
        }
    }
}