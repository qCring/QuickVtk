#pragma once

#include "quickVtkInterpolatingSubdivisionFilter.hpp"

#include <vtkLinearSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class LinearSubdivisionFilter : public InterpolatingSubdivisionFilter {
            Q_OBJECT
        private:
            static Qml::Register::Class<LinearSubdivisionFilter> Register;
            vtkSmartPointer<vtkLinearSubdivisionFilter> m_vtkLinearSubdivisionFilter;
        public:
            LinearSubdivisionFilter();
            auto setVtkLinearSubdivisionFilter(vtkSmartPointer<vtkLinearSubdivisionFilter>) -> void;
            auto getVtkLinearSubdivisionFilter() -> vtkSmartPointer<vtkLinearSubdivisionFilter>;
            ~LinearSubdivisionFilter();
        };
    }
}
