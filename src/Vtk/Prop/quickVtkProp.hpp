#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

#include <vtkSmartPointer.h>
#include <vtkProp.h>

namespace quick {

    namespace Vtk {

        class Viewer;

        class Prop : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool visibility READ getVisibility WRITE setVisibility NOTIFY visibilityChanged);
        private:
            bool m_initialized;
            vtkSmartPointer<vtkProp> m_vtkProp;
            QList<Viewer*> m_viewers;
            static Qml::Register::AbstractClass<Prop> Register;
        public:
            Prop();
            Prop(Prop*);
            auto update() -> void;
            auto setVisibility(bool) -> void;
            auto getVisibility() -> bool;
            auto linkViewer(Viewer*) -> void;
            auto unlinkViewer(Viewer*) -> void;
            auto setVtkProp(vtkSmartPointer<vtkProp>) -> void;
            auto getVtkProp() -> vtkSmartPointer<vtkProp>;
            virtual ~Prop();
        signals:
            void visibilityChanged();
        };
    }
}