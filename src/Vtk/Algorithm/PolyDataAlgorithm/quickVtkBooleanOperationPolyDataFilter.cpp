#include "quickVtkBooleanOperationPolyDataFilter.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::Class<BooleanOperationPolyDataFilter> BooleanOperationPolyDataFilter::Register;

        BooleanOperationPolyDataFilter::BooleanOperationPolyDataFilter() : PolyDataAlgorithm(vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New()) {
            this->m_vtkObject = vtkBooleanOperationPolyDataFilter::SafeDownCast(Algorithm::getVtkObject());
        }

        auto BooleanOperationPolyDataFilter::setOperation(Operation operation) -> void {
            this->m_vtkObject->SetOperation(operation);
            emit this->operationChanged();
            this->update();
        }

        auto BooleanOperationPolyDataFilter::getOperation() -> Operation {
            return (Operation) this->m_vtkObject->GetOperation();
        }

        auto BooleanOperationPolyDataFilter::setTolerance(float tolerance) -> void {
            this->m_vtkObject->SetTolerance(tolerance);
            emit this->toleranceChanged();
            this->update();
        }

        auto BooleanOperationPolyDataFilter::getTolerance() -> float {
            return this->m_vtkObject->GetTolerance();
        }

        auto BooleanOperationPolyDataFilter::setReorientDifferentCells(bool reorientDifferentCells) -> void {
            this->m_vtkObject->SetReorientDifferenceCells(reorientDifferentCells);
            emit this->reorientDifferentCellsChanged();
            this->update();
        }

        auto BooleanOperationPolyDataFilter::getReorientDifferentCells() -> bool {
            return this->m_vtkObject->GetReorientDifferenceCells();
        }
    }
}
