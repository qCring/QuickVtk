#include "quickVtkRandomSequence.hpp"

namespace quick::Vtk {
        
    Qml::Register::AbstractClass<RandomSequence> RandomSequence::Register(true);

    RandomSequence::RandomSequence(vtkSmartPointer<vtkRandomSequence> vtkObject) : Object(Object::Type::Other), m_vtkObject(vtkObject) {
    }

    auto RandomSequence::getVtkObject() -> vtkSmartPointer<vtkRandomSequence> {
        return this->m_vtkObject;
    }

    auto RandomSequence::setSeed(int seed) -> void {
        this->m_seed = seed;
        this->m_vtkObject->Initialize(seed);
    }

    auto RandomSequence::getSeed() -> int {
        return this->m_seed;
    }

    auto RandomSequence::initialize() -> void {
        if (this->m_vtkObject != nullptr) {
            this->m_vtkObject->Initialize(this->m_seed);
        }
    }
}
