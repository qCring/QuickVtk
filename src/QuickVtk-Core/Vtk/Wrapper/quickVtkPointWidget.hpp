#pragma once

#include "quickVtkWidget3D.hpp"

#include <vtkPointWidget.h>

namespace quick::Vtk {

    class PointWidget : public Widget3D {
        Q_OBJECT
        Q_PROPERTY(bool translationMode READ getTranslationMode WRITE setTranslationMode NOTIFY translationModeChanged);
        Q_PROPERTY(bool outline READ getOutline WRITE setOutline NOTIFY outlineChanged);
    private:
        static Qml::Register::Class<PointWidget> Register;
        vtkSmartPointer<vtkPointWidget> m_vtkObject = nullptr;
    public:
        PointWidget();
        auto setTranslationMode(bool) -> void;
        auto getTranslationMode() -> bool;
        auto setOutline(bool) -> void;
        auto getOutline() -> bool;
    signals:
        void translationModeChanged();
        void outlineChanged();
    };
}
