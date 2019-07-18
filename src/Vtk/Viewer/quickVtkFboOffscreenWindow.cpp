#include "quickVtkFboOffscreenWindow.hpp"
#include "quickVtkFboRenderer.hpp"
#include <vtkOpenGLState.h>

namespace quick {

    namespace Vtk {

        FboOffscreenWindow::FboOffscreenWindow() : QtParentRenderer(0) {
            this->OffScreenRenderingOn();
        }

        auto FboOffscreenWindow::New() -> FboOffscreenWindow* {
            return new FboOffscreenWindow();
        }

        auto FboOffscreenWindow::OpenGLInitState() -> void {
            
            this->MakeCurrent();
            initializeOpenGLFunctions();

            // Get OpenGL viewport size as configured by QtQuick
            int glViewport[4];
            glGetIntegerv(GL_VIEWPORT, glViewport);
            //std::cout << "FboOffscreenWindow::OpenGLInitState - glViewport: " << glViewport[0] << "," << glViewport[1] << "," << glViewport[2] << "," << glViewport[3] << "\n";

            // Do not know why exactly we need this, but it seems to help with syncing the Qt-VTK OpenGL states
            this->State->Initialize(this);

            // We now check the viewport size in vtkOpenGLState
            int vtkGLViewport[4];
            this->State->vtkglGetIntegerv(GL_VIEWPORT, vtkGLViewport);
            //std::cout << "FboOffscreenWindow::OpenGLInitState - vtkGLViewport: " << vtkGLViewport[0] << "," << vtkGLViewport[1] << "," << vtkGLViewport[2] << "," << vtkGLViewport[3] << "\n";

            // We adjust if they went out of sync
            if (vtkGLViewport[2] != glViewport[2] || vtkGLViewport[3] != glViewport[3])            
            {       
                //std::cout << "Need to adjust viewport..\n";
                if (glViewport[2] > 1 && glViewport[3] > 1)
                    this->State->vtkglViewport(0, 0, glViewport[2], glViewport[3]);
            }

            // We can now reset the GL state based on the VTK state
            Superclass::OpenGLInitState();
            glUseProgram(0);

            glEnable(GL_BLEND);
            // This one throws an invalid enum
            //glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT, GL_FASTEST);
            glDepthMask(GL_TRUE);
            
            //int glViewportAfter[4];
            //glGetIntegerv(GL_VIEWPORT, glViewportAfter);
            //std::cout << "FboOffscreenWindow::OpenGLInitState 2: " << glViewportAfter[0] << "," << glViewportAfter[1] << "," << glViewportAfter[2] << "," << glViewportAfter[3] << "\n";
        }

        auto FboOffscreenWindow::Render() -> void {
            if (this->QtParentRenderer) {
                this->QtParentRenderer->update();
            }
        }

        auto FboOffscreenWindow::InternalRender() -> void {
            Superclass::Render();
        }

        auto FboOffscreenWindow::SetFramebufferObject(QOpenGLFramebufferObject *fbo) -> void {
            this->BackLeftBuffer = this->FrontLeftBuffer = this->BackBuffer = this->FrontBuffer = static_cast<unsigned int>(GL_COLOR_ATTACHMENT0);

            auto size                    = fbo->size();

            this->Size[0]                   = size.width();
            this->Size[1]                   = size.height();
            this->NumberOfFrameBuffers      = 1;
            this->FrameBufferObject         = static_cast<unsigned int>(fbo->handle());
            this->DepthRenderBufferObject   = 0;
            this->TextureObjects[0]         = static_cast<unsigned int>(fbo->texture());
            this->OffScreenRendering        = 1;
            this->OffScreenUseFrameBuffer   = 1;
            this->Modified();
        }

        FboOffscreenWindow::~FboOffscreenWindow() {
            this->OffScreenRendering = 0;
        }
    }
}
