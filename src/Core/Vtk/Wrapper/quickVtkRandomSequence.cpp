#include "quickVtkRandomSequence.hpp"

namespace quick {
    namespace Vtk {
        
        Qml::Register::AbstractClass<RandomSequence> RandomSequence::Register(true);
    
        RandomSequence::RandomSequence(vtkSmartPointer<vtkRandomSequence> vtkObject) : Object(Object::Type::Other), m_vtkObject(vtkObject) {
        }
    
        auto RandomSequence::getVtkObject() -> vtkSmartPointer<vtkRandomSequence> {
            return this->m_vtkObject;
        }
    }
}
