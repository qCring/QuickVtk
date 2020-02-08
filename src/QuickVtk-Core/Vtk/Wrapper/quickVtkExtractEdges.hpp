#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkExtractEdges.h>

namespace quick::Vtk {

    class ExtractEdges : public PolyDataAlgorithm {
        Q_OBJECT
    private:
        static Qml::Register::Class<ExtractEdges> Register;
        vtkSmartPointer<vtkExtractEdges> m_vtkObject = nullptr;
    public:
        ExtractEdges();
    };
}
