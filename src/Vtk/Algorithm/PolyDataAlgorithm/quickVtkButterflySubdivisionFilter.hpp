#pragma once

#include "quickVtkInterpolatingSubdivisionFilter.hpp"

#include <vtkButterflySubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class ButterflySubdivisionFilter : public InterpolatingSubdivisionFilter {
            Q_OBJECT
        private:
            static Qml::Register::Class<ButterflySubdivisionFilter> Register;
            vtkSmartPointer<vtkButterflySubdivisionFilter> m_vtkButterflySubdivisionFilter;
        public:
            ButterflySubdivisionFilter();
            auto setVtkButterflySubdivisionFilter(vtkSmartPointer<vtkButterflySubdivisionFilter>) -> void;
            auto getVtkButterflySubdivisionFilter() -> vtkSmartPointer<vtkButterflySubdivisionFilter>;
            ~ButterflySubdivisionFilter();
        };
    }
}
