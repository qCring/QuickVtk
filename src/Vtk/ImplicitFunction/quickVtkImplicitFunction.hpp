#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkImplicitFunction.h>

namespace quick {

    namespace Vtk {

        class ImplicitFunction : public QObject {
            Q_OBJECT
        private:
            static Qml::Register::VtkAbstractClass<ImplicitFunction> Register;
            vtkSmartPointer<vtkImplicitFunction> m_vtkImplicitFunction;
        public:
            ImplicitFunction();
            ImplicitFunction(ImplicitFunction*);
            auto setVtkImplicitFunction(vtkSmartPointer<vtkImplicitFunction>) -> void;
            auto getVtkImplicitFunction() -> vtkSmartPointer<vtkImplicitFunction> ;
            ~ImplicitFunction();
        };
    }
}