#pragma once

#include "quickQmlRegister.hpp"
#include "quickVtkObject.hpp"

#include <vtkSmartPointer.h>
#include <vtkProp.h>

namespace quick {

    namespace Vtk {

        class Viewer;

        class Prop : public Object {
            Q_OBJECT
            Q_PROPERTY(bool visibility READ getVisibility WRITE setVisibility NOTIFY visibilityChanged);
        private:
            bool m_initialized;
            vtkSmartPointer<vtkProp> m_vtkObject = nullptr;
            QList<Viewer*> m_viewers;
            static Qml::Register::Symbol::AbstractClass<Prop> Register;
        public:
            Prop() = delete;
            Prop(vtkSmartPointer<vtkProp>);
            auto update() -> void;
            auto setVisibility(bool) -> void;
            auto getVisibility() -> bool;
            auto linkViewer(Viewer*) -> void;
            auto unlinkViewer(Viewer*) -> void;
            auto getVtkObject() -> vtkSmartPointer<vtkProp>;
            virtual ~Prop();
        signals:
            void visibilityChanged();
        };
    }
}
