#include "quickVtkTriangleFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<TriangleFilter> TriangleFilter::Register(true);

    TriangleFilter::TriangleFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkTriangleFilter>::New()) {
        this->m_vtkObject = vtkTriangleFilter::SafeDownCast(Algorithm::getVtkObject());
    }

    auto TriangleFilter::setPassVerts(bool pass) -> void {
        this->m_vtkObject->SetPassVerts(pass);
        this->update();
        emit this->passVertsChanged();
    }

    auto TriangleFilter::setPassLines(bool pass) -> void {
        this->m_vtkObject->SetPassLines(pass);
        this->update();
        emit this->passLinesChanged();
    }

    auto TriangleFilter::getPassVerts() -> bool {
        return this->m_vtkObject->GetPassVerts();
    }

    auto TriangleFilter::getPassLines() -> bool {
        return this->m_vtkObject->GetPassLines();
    }
}
