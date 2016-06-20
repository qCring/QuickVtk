#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkApproximatingSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class ApproximatingSubdivisionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int numberOfSubdivisions READ getNumberOfSubdivisions WRITE setNumberOfSubdivisions NOTIFY numberOfSubdivisionsChanged);
        private:
            static Qml::Register::AbstractClass<ApproximatingSubdivisionFilter> Register;
            vtkSmartPointer<vtkApproximatingSubdivisionFilter> m_vtkApproximatingSubdivisionFilter;
        public:
            ApproximatingSubdivisionFilter();
            ApproximatingSubdivisionFilter(ApproximatingSubdivisionFilter*);
            auto setVtkApproximatingSubdivisionFilter(vtkSmartPointer<vtkApproximatingSubdivisionFilter>) -> void;
            auto setNumberOfSubdivisions(int) -> void;
            auto getNumberOfSubdivisions() -> int;
            auto getVtkApproximatingSubdivisionFilter() -> vtkSmartPointer<vtkApproximatingSubdivisionFilter>;
            virtual ~ApproximatingSubdivisionFilter();
        signals:
            void numberOfSubdivisionsChanged();
        };
    }
}
