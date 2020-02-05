#include "quickVtkExtractEdges.hpp"

namespace quick::Vtk {

    Qml::Register::Class<ExtractEdges> ExtractEdges::Register(true);

    ExtractEdges::ExtractEdges() : PolyDataAlgorithm(vtkSmartPointer<vtkExtractEdges>::New()) {
        this->m_vtkObject = vtkExtractEdges::SafeDownCast(Algorithm::getVtkObject());
    }
}
