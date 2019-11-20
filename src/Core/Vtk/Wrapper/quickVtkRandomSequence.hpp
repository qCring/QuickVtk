#pragma once

#include "quickVtkObject.hpp"

#include <vtkRandomSequence.h>
#include <vtkSmartPointer.h>

namespace quick {

    namespace Vtk {

        class RandomSequence : public Object {
            Q_OBJECT
            Q_PROPERTY(int seed READ getSeed WRITE setSeed NOTIFY seedChanged);
        private:
            static Qml::Register::AbstractClass<RandomSequence> Register;
            vtkSmartPointer<vtkRandomSequence> m_vtkObject = nullptr;
            int m_seed;
        public:
            RandomSequence() = delete;
            RandomSequence(vtkSmartPointer<vtkRandomSequence>);
            auto getVtkObject() -> vtkSmartPointer<vtkRandomSequence>;
            auto setSeed(int) -> void;
            auto getSeed() -> int;
            auto initialize() -> void;
        signals:
            void seedChanged();
        };
    }
}
