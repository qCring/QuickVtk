#include "quickVtkMinimalStandardRandomSequence.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<MinimalStandardRandomSequence> MinimalStandardRandomSequence::Register(true);
    
        MinimalStandardRandomSequence::MinimalStandardRandomSequence() : RandomSequence(vtkSmartPointer<vtkMinimalStandardRandomSequence>::New()) {
            this->m_vtkObject = vtkMinimalStandardRandomSequence::SafeDownCast(RandomSequence::getVtkObject());
        }
    
        auto MinimalStandardRandomSequence::setSeed(int seed) -> void {
            this->m_vtkObject->SetSeed(seed);
            emit this->seedChanged();
        }
        
        auto MinimalStandardRandomSequence::getSeed() -> int {
            return this->m_vtkObject->GetSeed();
        }
    }
}
