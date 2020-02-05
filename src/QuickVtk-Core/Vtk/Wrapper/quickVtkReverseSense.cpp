#include "quickVtkReverseSense.hpp"

namespace quick::Vtk {

    Qml::Register::Class<ReverseSense> ReverseSense::Register(true);

    ReverseSense::ReverseSense() : PolyDataAlgorithm(vtkSmartPointer<vtkReverseSense>::New()) {
        this->m_vtkObject = vtkReverseSense::SafeDownCast(Algorithm::getVtkObject());
    }

    auto ReverseSense::setReverseCells(bool reverseCells) -> void {
        this->m_vtkObject->SetReverseCells(reverseCells);
        this->update();
        emit this->reverseCellsChanged();
    }

    auto ReverseSense::getReverseCells() -> bool {
        return this->m_vtkObject->GetReverseCells();
    }

    auto ReverseSense::setReverseNormals(bool reverseNormals) -> void {
        this->m_vtkObject->SetReverseNormals(reverseNormals);
        this->update();
        emit this->reverseNormalsChanged();
    }

    auto ReverseSense::getReverseNormals() -> bool {
        return this->m_vtkObject->GetReverseNormals();
    }
}
