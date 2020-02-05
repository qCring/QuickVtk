#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>

#include <vtkExternalOpenGLRenderWindow.h>

namespace quick::Vtk {

    class FboRenderer;

    class FboOffscreenWindow : public vtkExternalOpenGLRenderWindow, protected QOpenGLFunctions {
    public:
        FboRenderer* QtParentRenderer = nullptr;
        static auto New() -> FboOffscreenWindow*;
        virtual auto OpenGLInitState() -> void override;
        auto Render() -> void override;
        auto InternalRender() -> void;
        auto SetFramebufferObject(QOpenGLFramebufferObject*) -> void;
    protected:
        FboOffscreenWindow();
        ~FboOffscreenWindow();
    };
}
