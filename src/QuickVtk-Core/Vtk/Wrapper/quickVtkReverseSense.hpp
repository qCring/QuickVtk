#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkReverseSense.h>

namespace quick {
    namespace Vtk {

        class ReverseSense : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(bool reverseCells READ getReverseCells WRITE setReverseCells NOTIFY reverseCellsChanged);
            Q_PROPERTY(bool reverseNormals READ getReverseNormals WRITE setReverseNormals NOTIFY reverseNormalsChanged);
        private:
            static Qml::Register::Class<ReverseSense> Register;
            vtkSmartPointer<vtkReverseSense> m_vtkObject = nullptr;
        public:
            ReverseSense();
            auto setReverseCells(bool) -> void;
            auto getReverseCells() -> bool;
            auto setReverseNormals(bool) -> void;
            auto getReverseNormals() -> bool;
        signals:
            void reverseCellsChanged();
            void reverseNormalsChanged();
        };
    }
}
