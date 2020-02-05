#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkDensifyPolyData.h>

namespace quick::Vtk {

    class DensifyPolyData : public PolyDataAlgorithm {
        Q_OBJECT
        Q_PROPERTY(int numberOfSubdivisions READ getNumberOfSubdivisions WRITE setNumberOfSubdivisions NOTIFY numberOfSubdivisionsChanged);
    private:
        static Qml::Register::Class<DensifyPolyData> Register;
        vtkSmartPointer<vtkDensifyPolyData> m_vtkObject = nullptr;
    public:
        DensifyPolyData();
        auto setNumberOfSubdivisions(int) -> void;
        auto getNumberOfSubdivisions() -> int;
    signals:
        void numberOfSubdivisionsChanged();
    };
}
