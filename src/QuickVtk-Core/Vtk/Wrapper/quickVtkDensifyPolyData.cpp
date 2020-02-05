#include "quickVtkDensifyPolyData.hpp"

namespace quick::Vtk {

    Qml::Register::Class<DensifyPolyData> DensifyPolyData::Register(true);

    DensifyPolyData::DensifyPolyData() : PolyDataAlgorithm(vtkSmartPointer<vtkDensifyPolyData>::New()) {
        this->m_vtkObject = vtkDensifyPolyData::SafeDownCast(Algorithm::getVtkObject());
    }

    auto DensifyPolyData::setNumberOfSubdivisions(int numberOfSubdivisions) -> void {
        this->m_vtkObject->SetNumberOfSubdivisions(numberOfSubdivisions);
        this->update();
        emit this->numberOfSubdivisionsChanged();
    }

    auto DensifyPolyData::getNumberOfSubdivisions() -> int {
        return this->m_vtkObject->GetNumberOfSubdivisions();
    }
}
