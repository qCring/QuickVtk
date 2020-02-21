#pragma once

#include "quickVtkObject.hpp"
#include "quickMathVector3.hpp"

#include <vtkSmartPointer.h>
#include <vtkInteractorObserver.h>
#include <vtkRenderWindowInteractor.h>

namespace quick::Vtk {

    class InteractorObserver : public Object {
        Q_OBJECT
        Q_PROPERTY(bool enabled READ getEnabled WRITE setEnabled NOTIFY enabledChanged);
    private:
        static Qml::Register::AbstractClass<InteractorObserver> Register;
        vtkSmartPointer<vtkInteractorObserver> m_vtkObject = nullptr;
        vtkSmartPointer<vtkRenderWindowInteractor> m_interactor = nullptr;
        bool m_enabled = true;
    public:
        InteractorObserver(vtkSmartPointer<vtkInteractorObserver>);
        auto getVtkObject() -> vtkSmartPointer<vtkInteractorObserver>;
        auto setEnabled(bool) -> void;
        auto getEnabled() -> bool;
        auto setInteractor(vtkSmartPointer<vtkRenderWindowInteractor>) -> void;
    signals:
        void enabledChanged();
    };
}
