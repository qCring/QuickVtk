#pragma once

#include "quickVtkImplicitFunction.hpp"
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
            static Qml::Register::Class<Cutter> Register;
            ImplicitFunction::cb_t m_cutFunctionCb;
            ImplicitFunction* m_cutFunction = nullptr;
            vtkSmartPointer<vtkCutter> m_vtkObject = nullptr;
        public:
            Cutter();
            auto updateCutFunction() -> void;
            auto setCutFunction(ImplicitFunction*) -> void;
            auto getCutFunction() -> ImplicitFunction*;
            ~Cutter();
        signals:
            void cutFunctionChanged();
        };
    }
}
