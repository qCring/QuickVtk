#include "quickVtkApproximatingSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::AbstractClass<ApproximatingSubdivisionFilter> ApproximatingSubdivisionFilter::Register;


        ApproximatingSubdivisionFilter::ApproximatingSubdivisionFilter(vtkSmartPointer<vtkApproximatingSubdivisionFilter> vtkObject) : PolyDataAlgorithm(vtkObject), m_vtkObject(vtkObject) {
        }

        auto ApproximatingSubdivisionFilter::setNumberOfSubdivisions(int subdivisions) -> void {
            this->m_vtkObject->SetNumberOfSubdivisions(subdivisions);
            emit this->numberOfSubdivisionsChanged();
            this->update();
        }

        auto ApproximatingSubdivisionFilter::getNumberOfSubdivisions() -> int {
            return this->m_vtkObject->GetNumberOfSubdivisions();
        }
    }
}