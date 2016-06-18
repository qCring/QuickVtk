#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QList>

#include <vtkSmartPointer.h>
#include <vtkImplicitFunction.h>

namespace quick {

    namespace Vtk {

        class ImplicitFunction : public QObject {
            Q_OBJECT
        public:
            using cb_t = std::function<void(void)>;
        private:
            static Qml::Register::AbstractClass<ImplicitFunction> Register;
            vtkSmartPointer<vtkImplicitFunction> m_vtkImplicitFunction;
            QList<cb_t*> m_callbacks;
        public:
            ImplicitFunction(ImplicitFunction*);
            auto update() -> void;
            auto addCallback(cb_t&&) -> void;
            auto removeCallback(cb_t&&) -> void;
            auto setVtkImplicitFunction(vtkSmartPointer<vtkImplicitFunction>) -> void;
            auto getVtkImplicitFunction() -> vtkSmartPointer<vtkImplicitFunction> ;
            ~ImplicitFunction();
        };
    }
}