#include "quickVtkMinimalStandardRandomSequence.hpp"

namespace quick {
    namespace Vtk {

        Qml::Register::Class<MinimalStandardRandomSequence> MinimalStandardRandomSequence::Register(true);
    
        MinimalStandardRandomSequence::MinimalStandardRandomSequence() : RandomSequence(vtkSmartPointer<vtkMinimalStandardRandomSequence>::New()) {
            this->m_vtkObject = vtkMinimalStandardRandomSequence::SafeDownCast(RandomSequence::getVtkObject());
        }    
    }
}
