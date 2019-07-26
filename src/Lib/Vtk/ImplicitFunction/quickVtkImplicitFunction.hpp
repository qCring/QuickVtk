#pragma once

#include "quickQmlRegister.hpp"
#include "quickVtkObject.hpp"

#include <QList>

#include <vtkSmartPointer.h>
#include <vtkImplicitFunction.h>

namespace quick {

    namespace Vtk {

        class ImplicitFunction : public Object {
            Q_OBJECT
        public:
            using cb_t = std::function<void(void)>;
        private:
            static Qml::Register::Symbol::AbstractClass<ImplicitFunction> Register;
            vtkSmartPointer<vtkImplicitFunction> m_vtkObject = nullptr;
            QList<cb_t*> m_callbacks;
        public:
            ImplicitFunction() = delete;
            ImplicitFunction(vtkSmartPointer<vtkImplicitFunction>);
            auto update() -> void;
            auto addCallback(cb_t&&) -> void;
            auto removeCallback(cb_t&&) -> void;
            auto getVtkObject() -> vtkSmartPointer<vtkImplicitFunction>;
            ~ImplicitFunction();
        };
    }
}
