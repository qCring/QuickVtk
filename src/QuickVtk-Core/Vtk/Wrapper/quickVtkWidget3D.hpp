#pragma once

#include "quickVtkInteractorObserver.hpp"

#include <vtk3DWidget.h>

namespace quick::Vtk {
    
    class Prop3D;

    class Widget3D : public InteractorObserver {
        Q_OBJECT
        Q_PROPERTY(quick::Vtk::Prop3D* prop3D READ getProp3D WRITE setProp3D NOTIFY prop3DChanged);
        Q_PROPERTY(qreal placeFactor READ getPlaceFactor WRITE setPlaceFactor NOTIFY placeFactorChanged);
        Q_PROPERTY(qreal handleSize READ getHandleSize WRITE setHandleSize NOTIFY handleSizeChanged);
    private:
        static Qml::Register::AbstractClass<Widget3D> Register;
        vtkSmartPointer<vtk3DWidget> m_vtkObject = nullptr;
        Prop3D* m_prop3D = nullptr;
    public:
        Widget3D(vtkSmartPointer<vtk3DWidget>);
        auto getVtkObject() -> vtkSmartPointer<vtk3DWidget>;
        auto setProp3D(Prop3D*) -> void;
        auto getProp3D() -> Prop3D*;
        auto setPlaceFactor(qreal) -> void;
        auto getPlaceFactor() -> qreal;
        auto setHandleSize(qreal) -> void;
        auto getHandleSize() -> qreal;
    signals:
        void prop3DChanged();
        void placeFactorChanged();
        void handleSizeChanged();
    };
}
