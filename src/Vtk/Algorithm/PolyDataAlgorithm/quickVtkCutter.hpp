#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkCutter.h>

namespace quick
{
    namespace Vtk
    {
        class ImplicitFunction;

        class Cutter : public PolyDataAlgorithm
        {
            Q_OBJECT
            Q_PROPERTY(quick::Vtk::ImplicitFunction* cutFunction READ getCutFunction WRITE setCutFunction NOTIFY cutFunctionChanged);
        private:
            static Qml::Register::VtkClass<Cutter> Register;
            ImplicitFunction* m_cutFunction;
            vtkSmartPointer<vtkCutter> m_vtkCutter;
        public:
            Cutter();
            Cutter(Cutter*);
            auto setCutFunction(ImplicitFunction*) -> void;
            auto getCutFunction() -> ImplicitFunction*;
            ~Cutter();
        signals:
            void cutFunctionChanged();
        };
    }
}
