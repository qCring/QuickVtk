#include "quickVtkVertexGlyphFilter.hpp"

namespace quick::Vtk {

    Qml::Register::Class<VertexGlyphFilter> VertexGlyphFilter::Register(true);

    VertexGlyphFilter::VertexGlyphFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkVertexGlyphFilter>::New()) {
    }
}
