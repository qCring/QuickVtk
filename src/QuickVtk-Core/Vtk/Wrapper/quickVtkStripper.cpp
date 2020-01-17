#include "quickVtkStripper.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<Stripper> Stripper::Register(true);
        
        Stripper::Stripper() : PolyDataAlgorithm(vtkSmartPointer<vtkStripper>::New()) {
            this->m_vtkObject = vtkStripper::SafeDownCast(Algorithm::getVtkObject());
        }
    
        auto Stripper::setMaximumLength(int maximumLength) -> void {
            this->m_vtkObject->SetMaximumLength(maximumLength);
            this->update();
            emit this->passThroughCellIdsChanged();
        }
    
        auto Stripper::getMaximumLength() -> int {
            return this->m_vtkObject->GetMaximumLength();
        }
    
        auto Stripper::setPassCellDataAsFieldData(bool passCellDataAsFieldData) -> void {
            this->m_vtkObject->SetPassCellDataAsFieldData(passCellDataAsFieldData);
            this->update();
            emit this->passCellDataAsFieldDataChanged();
        }
    
        auto Stripper::getPassCellDataAsFieldData() -> bool {
            return this->m_vtkObject->GetPassCellDataAsFieldData();
        }
    
        auto Stripper::setPassThroughCellIds(bool passThroughCellIds) -> void {
            this->m_vtkObject->SetPassThroughCellIds(passThroughCellIds);
            this->update();
            emit this->passThroughCellIdsChanged();
        }
    
        auto Stripper::getPassThroughCellIds() -> bool {
            return this->m_vtkObject->GetPassThroughCellIds();
        }
    
        auto Stripper::setPassThroughPointIds(bool passThroughPointIds) -> void {
            this->m_vtkObject->SetPassThroughPointIds(passThroughPointIds);
            this->update();
            emit this->passThroughPointIdsChanged();
        }
    
        auto Stripper::getPassThroughPointIds() -> bool {
            return this->m_vtkObject->GetPassThroughPointIds();
        }
    
        auto Stripper::setJoinContiguousSegments(bool joinContiguousSegments) -> void {
            this->m_vtkObject->SetJoinContiguousSegments(joinContiguousSegments);
            this->update();
            emit this->joinContiguousSegmentsChanged();
        }
    
        auto Stripper::getJoinContiguousSegments() -> bool {
            return this->m_vtkObject->GetJoinContiguousSegments();
        }
    }
}
