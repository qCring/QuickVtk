#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkInterpolatingSubdivisionFilter.h>

namespace quick::Vtk {

    class InterpolatingSubdivisionFilter : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(int numberOfSubdivisions READ getNumberOfSubdivisions WRITE setNumberOfSubdivisions NOTIFY numberOfSubdivisionsChanged);
    private:
        static Qml::Register::AbstractClass<InterpolatingSubdivisionFilter> Register;
        vtkSmartPointer<vtkInterpolatingSubdivisionFilter> m_vtkObject = nullptr;
    public:
        InterpolatingSubdivisionFilter(vtkSmartPointer<vtkInterpolatingSubdivisionFilter>);
        auto setNumberOfSubdivisions(int) -> void;
        auto getNumberOfSubdivisions() -> int;
    signals:
        void numberOfSubdivisionsChanged();
    };
}
