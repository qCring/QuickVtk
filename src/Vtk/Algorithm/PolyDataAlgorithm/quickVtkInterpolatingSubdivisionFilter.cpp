#include "quickVtkInterpolatingSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<InterpolatingSubdivisionFilter> InterpolatingSubdivisionFilter::Register;

        InterpolatingSubdivisionFilter::InterpolatingSubdivisionFilter(vtkSmartPointer<vtkInterpolatingSubdivisionFilter> vtkObject) : PolyDataAlgorithm(vtkObject) {
            this->m_vtkObject = vtkObject;
        }

        auto InterpolatingSubdivisionFilter::setNumberOfSubdivisions(int value) -> void {
            this->m_vtkObject->SetNumberOfSubdivisions(value);
            emit this->numberOfSubdivisionsChanged();
            this->update();
        }

        auto InterpolatingSubdivisionFilter::getNumberOfSubdivisions() -> int {
            return this->m_vtkObject->GetNumberOfSubdivisions();
        }
    }
}