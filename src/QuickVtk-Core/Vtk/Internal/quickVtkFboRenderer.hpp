#pragma once

#include <QQuickFramebufferObject>

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <QMouseEvent>

namespace quick::Vtk {

    class FboOffscreenWindow;

    class FboRenderer : public QQuickFramebufferObject::Renderer {
        friend class FboOffscreenWindow;
    private:
        FboOffscreenWindow* m_fboOffscreenWindow = nullptr;
        QOpenGLFramebufferObject* m_fbo = nullptr;
    public:
        vtkSmartPointer<vtkRenderWindowInteractor> m_interactor = nullptr;
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
    public:
        FboRenderer(FboOffscreenWindow*);
        auto synchronize(QQuickFramebufferObject*) -> void override;
        auto render() -> void override;
        auto onMouseEvent(QMouseEvent*) -> void;
        auto createFramebufferObject(const QSize&) -> QOpenGLFramebufferObject* override;
        ~FboRenderer();
    };
}
