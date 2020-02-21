#pragma once

#include "quickVtkWidget3D.hpp"
#include "quickMathVector3.hpp"

#include <vtkLineWidget.h>

namespace quick::Vtk {

    class LineWidget : public Widget3D {
        Q_OBJECT
        Q_PROPERTY(quick::Math::Vector3* point1 READ getPoint1 CONSTANT);
        Q_PROPERTY(quick::Math::Vector3* point2 READ getPoint2 CONSTANT);
    private:
        static Qml::Register::Class<LineWidget> Register;
        vtkSmartPointer<vtkLineWidget> m_vtkObject = nullptr;
        Math::Vector3* m_point1 = nullptr;
        Math::Vector3* m_point2 = nullptr;
    private:
        auto ProcessInteractionEvent(vtkObject*, long unsigned int vtkNotUsed(eventId), void* vtkNotUsed(callData)) -> void;
        auto getPoint1() -> Math::Vector3*;
        auto getPoint2() -> Math::Vector3*;
    public:
        LineWidget();
    };
}
