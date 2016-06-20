#pragma once

#include "quickVtkApproximatingSubdivisionFilter.hpp"

#include <vtkLoopSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class LoopSubdivisionFilter : public ApproximatingSubdivisionFilter {
            Q_OBJECT
        private:
            static Qml::Register::Class<LoopSubdivisionFilter> Register;
            vtkSmartPointer<vtkLoopSubdivisionFilter> m_vtkLoopSubdivisionFilter;
        public:
            LoopSubdivisionFilter();
            auto setVtkLoopSubdivisionFilter(vtkSmartPointer<vtkLoopSubdivisionFilter>) -> void;
            auto getVtkLoopSubdivisionFilter() -> vtkSmartPointer<vtkLoopSubdivisionFilter>;
            ~LoopSubdivisionFilter();
        };
    }
}
