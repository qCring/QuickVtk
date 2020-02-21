#include "quickVtkFboRenderer.hpp"
#include "quickVtkFboOffscreenWindow.hpp"
#include "quickVtkViewer.hpp"

#ifdef _MSC_VER
#include "quickVtkWin32Interactor.hpp"
#endif

#ifdef __linux__
#include "quickVtkGenericInteractor.hpp"
#endif

#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <vtkCommand.h>

namespace quick::Vtk {

    FboRenderer::FboRenderer(FboOffscreenWindow *offscreenWindow) : m_fboOffscreenWindow(offscreenWindow), m_fbo(0) {
        m_fboOffscreenWindow->Register(NULL);
        m_fboOffscreenWindow->QtParentRenderer = this;

#ifdef __APPLE__
        m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
#endif
        
#ifdef __linux__
        m_interactor = vtkSmartPointer<quick::Vtk::GenericInteractor>::New();
#endif
        
#ifdef _MSC_VER
        m_interactor = vtkSmartPointer<quick::Vtk::Win32Interactor>::New();
#endif
        
        m_interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        
        m_interactor->SetRenderWindow(offscreenWindow);
        m_interactor->Initialize();
        m_interactor->SetInteractorStyle(m_interactorStyle);
    }

    auto FboRenderer::synchronize(QQuickFramebufferObject* fbo) -> void {
        if (!m_fbo) {
            auto viewer = static_cast<Viewer*>(fbo);
            viewer->init();
        }
    }

    auto FboRenderer::render() -> void {
        m_interactor->Disable();
        m_fboOffscreenWindow->PushState();
        m_fboOffscreenWindow->OpenGLInitState();
        m_fboOffscreenWindow->InternalRender();
        m_fboOffscreenWindow->PopState();
        m_interactor->Enable();
    }

    auto FboRenderer::createFramebufferObject(const QSize &size) -> QOpenGLFramebufferObject* {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::Depth);
        m_fbo = new QOpenGLFramebufferObject(size, format);
        m_fboOffscreenWindow->SetFramebufferObject(m_fbo);
        
        return m_fbo;
    }
    
    auto FboRenderer::setPixelRatio(qreal pixelRatio) -> void {
        this->m_pixelRatio = pixelRatio;
    }

    auto FboRenderer::onMouseEvent(QMouseEvent* event) -> void {
        if(this->m_interactor == nullptr || event == nullptr) {
            return;
        }
        
        if(!this->m_interactor->GetEnabled()) {
            return;
        }
        
        auto mouse_x = event->x() * m_pixelRatio;
        auto mouse_y = this->m_fbo->size().height() - event->y() * m_pixelRatio;
        
        this->m_interactor->SetEventInformation(mouse_x, mouse_y, (event->modifiers() & Qt::ControlModifier), (event->modifiers() & Qt::ShiftModifier));
        
        auto command = vtkCommand::NoEvent;

        if (event->type() == QEvent::MouseMove) {
            command = vtkCommand::MouseMoveEvent;
        }

        else if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) {
            switch (event->button()) {
                case Qt::LeftButton:    command = vtkCommand::LeftButtonPressEvent; break;
                case Qt::RightButton:   command = vtkCommand::RightButtonPressEvent; break;
                case Qt::MidButton:     command = vtkCommand::MiddleButtonPressEvent; break;
                default: break;
            }
        }

        else if (event->type() == QEvent::MouseButtonRelease) {
            switch (event->button()) {
                case Qt::LeftButton:    command = vtkCommand::LeftButtonReleaseEvent; break;
                case Qt::RightButton:   command = vtkCommand::RightButtonReleaseEvent; break;
                case Qt::MidButton:     command = vtkCommand::MiddleButtonReleaseEvent; break;
                default: break;
            }
        }

        this->m_interactor->InvokeEvent(command);
    }

    FboRenderer::~FboRenderer() {
        this->m_fboOffscreenWindow->QtParentRenderer = nullptr;
        this->m_fboOffscreenWindow->Delete();
    }
}
