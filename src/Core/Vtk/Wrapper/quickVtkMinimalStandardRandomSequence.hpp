#pragma once

#include "quickVtkRandomSequence.hpp"

#include <vtkMinimalStandardRandomSequence.h>

namespace quick {

    namespace Vtk {

        class MinimalStandardRandomSequence : public RandomSequence {
            Q_OBJECT
        private:
            static Qml::Register::Class<MinimalStandardRandomSequence> Register;
            vtkSmartPointer<vtkMinimalStandardRandomSequence> m_vtkObject;
        public:
            MinimalStandardRandomSequence();
        };
    }
}
