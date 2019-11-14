#pragma once

#include "quickVtkObject.hpp"

#include <vtkRandomSequence.h>
#include <vtkSmartPointer.h>

namespace quick {

    namespace Vtk {

        class RandomSequence : public Object {
            Q_OBJECT
        private:
            static Qml::Register::AbstractClass<RandomSequence> Register;
            vtkSmartPointer<vtkRandomSequence> m_vtkObject;
        public:
            RandomSequence() = delete;
            RandomSequence(vtkSmartPointer<vtkRandomSequence>);
            auto getVtkObject() -> vtkSmartPointer<vtkRandomSequence>;
        };
    }
}
