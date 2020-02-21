#pragma once

#include <QQuickFramebufferObject>

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackballActor.h>

#include <QMouseEvent>

namespace quick::Vtk {

    class FboOffscreenWindow;

    class FboRenderer : public QQuickFramebufferObject::Renderer {
        friend class FboOffscreenWindow;
    private:
        FboOffscreenWindow* m_fboOffscreenWindow = nullptr;
        QOpenGLFramebufferObject* m_fbo = nullptr;
        qreal m_pixelRatio = 1.0f;
    public:
        vtkSmartPointer<vtkRenderWindowInteractor> m_interactor = nullptr;
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
    public:
        FboRenderer(FboOffscreenWindow*);
        auto setPixelRatio(qreal) -> void;
        auto synchronize(QQuickFramebufferObject*) -> void override;
        auto render() -> void override;
        auto onMouseEvent(QMouseEvent*) -> void;
        auto createFramebufferObject(const QSize&) -> QOpenGLFramebufferObject* override;
        ~FboRenderer();
    };
}
