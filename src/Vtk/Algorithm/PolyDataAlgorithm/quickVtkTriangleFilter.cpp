#include "quickVtkTriangleFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Class<TriangleFilter> TriangleFilter::Register;

        TriangleFilter::TriangleFilter() : PolyDataAlgorithm(this) {
            this->m_vtkTriangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
            PolyDataAlgorithm::setVtkPolyDataAlgorithm(m_vtkTriangleFilter);
        }

        auto TriangleFilter::setPassVerts(bool pass) -> void {
            this->m_vtkTriangleFilter->SetPassVerts(pass);
            this->update();
            emit this->passVertsChanged();
        }

        auto TriangleFilter::setPassLines(bool pass) -> void {
            this->m_vtkTriangleFilter->SetPassLines(pass);
            this->update();
            emit this->passLinesChanged();
        }

        auto TriangleFilter::getPassVerts() -> bool {
            return this->m_vtkTriangleFilter->GetPassVerts();
        }

        auto TriangleFilter::getPassLines() -> bool {
            return this->m_vtkTriangleFilter->GetPassLines();
        }

        TriangleFilter::~TriangleFilter() {
            this->m_vtkTriangleFilter = 0;
        }
    }
}