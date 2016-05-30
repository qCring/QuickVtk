#include "quickVtkFboOffscreenWindow.hpp"
#include "quickVtkFboRenderer.hpp"

namespace quick
{
    namespace Vtk
    {
        FboOffscreenWindow::FboOffscreenWindow() : QtParentRenderer(0) { }

        auto FboOffscreenWindow::New() -> FboOffscreenWindow*
        {
            return new FboOffscreenWindow();
        }

        auto FboOffscreenWindow::OpenGLInitState() -> void
        {
            Superclass::OpenGLInitState();

            this->MakeCurrent();
            initializeOpenGLFunctions();

            Superclass::OpenGLInitState();
            glUseProgram(0);

            glEnable(GL_BLEND);
            glHint(GL_CLIP_VOLUME_CLIPPING_HINT_EXT, GL_FASTEST);
            glDepthMask(GL_TRUE);
        }

        auto FboOffscreenWindow::Render() -> void
        {
            if (this->QtParentRenderer)
                this->QtParentRenderer->update();
                }

        auto FboOffscreenWindow::InternalRender() -> void
        {
            Superclass::Render();
        }

        auto FboOffscreenWindow::SetFramebufferObject(QOpenGLFramebufferObject *fbo) -> void
        {
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

        FboOffscreenWindow::~FboOffscreenWindow()
        {
            this->OffScreenRendering = 0;
        }
    }
}
