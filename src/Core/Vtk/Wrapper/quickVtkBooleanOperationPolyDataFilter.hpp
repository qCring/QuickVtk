#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkBooleanOperationPolyDataFilter.h>

namespace quick {

    namespace Vtk {

        class BooleanOperationPolyDataFilter : public PolyDataAlgorithm {
            Q_OBJECT
        public:
            enum Operation {
                Union = vtkBooleanOperationPolyDataFilter::VTK_UNION,
                Intersection = vtkBooleanOperationPolyDataFilter::VTK_INTERSECTION,
                Difference = vtkBooleanOperationPolyDataFilter::VTK_DIFFERENCE
            };
        private:
            Q_ENUM(Operation);
            Q_PROPERTY(Operation operation READ getOperation WRITE setOperation NOTIFY operationChanged);
            Q_PROPERTY(qreal tolerance READ getTolerance WRITE setTolerance NOTIFY toleranceChanged);
            Q_PROPERTY(bool reorientDifferentCells READ getReorientDifferentCells WRITE setReorientDifferentCells NOTIFY reorientDifferentCellsChanged);
        private:
            static Qml::Register::Class<BooleanOperationPolyDataFilter> Register;
            vtkSmartPointer<vtkBooleanOperationPolyDataFilter> m_vtkObject;
        public:
            BooleanOperationPolyDataFilter();
            auto setOperation(Operation) -> void;
            auto getOperation() -> Operation;
            auto setTolerance(qreal) -> void;
            auto getTolerance() -> qreal;
            auto setReorientDifferentCells(bool) -> void;
            auto getReorientDifferentCells() -> bool;
        signals:
            void operationChanged();
            void toleranceChanged();
            void reorientDifferentCellsChanged();
        };
    }
}
