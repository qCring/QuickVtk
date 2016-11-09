#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkVertexGlyphFilter.h>

namespace quick {

    namespace Vtk {

        class VertexGlyphFilter : public PolyDataAlgorithm {
            Q_OBJECT

        private:
            static Qml::Register::Symbol::Class<VertexGlyphFilter> Register;
        public:
            VertexGlyphFilter();
        };
    }
}
