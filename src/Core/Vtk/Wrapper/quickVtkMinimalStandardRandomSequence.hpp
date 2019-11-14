#pragma once

#include "quickVtkRandomSequence.hpp"

#include <vtkMinimalStandardRandomSequence.h>

namespace quick {

    namespace Vtk {

        class MinimalStandardRandomSequence : public RandomSequence {
            Q_OBJECT
            Q_PROPERTY(int seed READ getSeed WRITE setSeed NOTIFY seedChanged);
        private:
            static Qml::Register::Class<MinimalStandardRandomSequence> Register;
            vtkSmartPointer<vtkMinimalStandardRandomSequence> m_vtkObject;
        public:
            MinimalStandardRandomSequence();
            auto getSeed() -> int;
            auto setSeed(int) -> void;
        signals:
            void seedChanged();
        };
    }
}
