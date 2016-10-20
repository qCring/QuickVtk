#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkApproximatingSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class ApproximatingSubdivisionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int numberOfSubdivisions READ getNumberOfSubdivisions WRITE setNumberOfSubdivisions NOTIFY numberOfSubdivisionsChanged);
        private:
            static Qml::Register::Symbol::AbstractClass<ApproximatingSubdivisionFilter> Register;
            vtkSmartPointer<vtkApproximatingSubdivisionFilter> m_vtkObject;
        public:
            ApproximatingSubdivisionFilter(vtkSmartPointer<vtkApproximatingSubdivisionFilter>);
            auto setNumberOfSubdivisions(int) -> void;
            auto getNumberOfSubdivisions() -> int;
        signals:
            void numberOfSubdivisionsChanged();
        };
    }
}
