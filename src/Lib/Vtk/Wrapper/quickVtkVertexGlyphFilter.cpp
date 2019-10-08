#include "quickVtkVertexGlyphFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<VertexGlyphFilter> VertexGlyphFilter::Register(true);

        VertexGlyphFilter::VertexGlyphFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkVertexGlyphFilter>::New()) {
        }
    }
}
