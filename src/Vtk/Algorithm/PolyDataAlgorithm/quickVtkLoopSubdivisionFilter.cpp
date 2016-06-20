#include "quickVtkLoopSubdivisionFilter.hpp"

namespace quick {

    namespace Vtk {
        Qml::Register::Class<LoopSubdivisionFilter> LoopSubdivisionFilter::Register;

        LoopSubdivisionFilter::LoopSubdivisionFilter() : ApproximatingSubdivisionFilter(this) {
            this->setVtkLoopSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>::New());
        }

        auto LoopSubdivisionFilter::setVtkLoopSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter> vtkLoopSubdivisionFilter) -> void {
            this->m_vtkLoopSubdivisionFilter = vtkLoopSubdivisionFilter;
            ApproximatingSubdivisionFilter::setVtkApproximatingSubdivisionFilter(vtkLoopSubdivisionFilter);
        }

        auto LoopSubdivisionFilter::getVtkLoopSubdivisionFilter() -> vtkSmartPointer<vtkLoopSubdivisionFilter> {
            return this->m_vtkLoopSubdivisionFilter;
        }

        LoopSubdivisionFilter::~LoopSubdivisionFilter() {
            this->m_vtkLoopSubdivisionFilter = nullptr;
        }
    }
}