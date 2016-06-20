#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkInterpolatingSubdivisionFilter.h>

namespace quick {

    namespace Vtk {

        class InterpolatingSubdivisionFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(int numberOfSubdivisions READ getNumberOfSubdivisions WRITE setNumberOfSubdivisions NOTIFY numberOfSubdivisionsChanged);
        private:
            static Qml::Register::AbstractClass<InterpolatingSubdivisionFilter> Register;
            vtkSmartPointer<vtkInterpolatingSubdivisionFilter> m_vtkInterpolatingSubdivisionFilter;
        public:
            InterpolatingSubdivisionFilter();
            InterpolatingSubdivisionFilter(InterpolatingSubdivisionFilter*);
            auto setNumberOfSubdivisions(int) -> void;
            auto setVtkInterpolatingSubdivisionFilter(vtkSmartPointer<vtkInterpolatingSubdivisionFilter>) -> void;
            auto getNumberOfSubdivisions() -> int;
            auto getVtkInterpolatingSubdivisionFilter() -> vtkSmartPointer<vtkInterpolatingSubdivisionFilter>;
            virtual ~InterpolatingSubdivisionFilter();
        signals:
            void numberOfSubdivisionsChanged();
        };
    }
}
