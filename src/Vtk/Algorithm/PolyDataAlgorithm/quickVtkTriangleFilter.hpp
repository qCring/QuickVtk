#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkTriangleFilter.h>

namespace quick {

    namespace Vtk {

        class TriangleFilter : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(bool passVerts READ getPassVerts WRITE setPassVerts NOTIFY passVertsChanged);
            Q_PROPERTY(bool passLines READ getPassLines WRITE setPassLines NOTIFY passLinesChanged);
        private:
            static Qml::Register::VtkClass<TriangleFilter> Register;
            vtkSmartPointer<vtkTriangleFilter> m_vtkTriangleFilter;
        public:
            TriangleFilter();
            auto setPassVerts(bool) -> void;
            auto setPassLines(bool) -> void;
            auto getPassVerts() -> bool;
            auto getPassLines() -> bool;
            ~TriangleFilter();
        signals:
            void passVertsChanged();
            void passLinesChanged();
        };
    }
}
