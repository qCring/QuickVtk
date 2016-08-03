#include "quickVtkProp.hpp"
#include "quickVtkViewer.hpp"
#include "quickVtkFboRenderer.hpp"
#include "quickVtkFboOffscreenWindow.hpp"

#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>

namespace quick {

    namespace Vtk {

        Qml::Register::Class<Viewer> Viewer::Register;

        Viewer::Viewer() {
            this->m_renderer = 0;
            m_win = FboOffscreenWindow::New();

            this->setMirrorVertically(true);
        }

        auto Viewer::init() -> void {
            auto rw = this->GetRenderWindow();
            this->m_renderer = vtkSmartPointer<vtkRenderer>::New();
            rw->AddRenderer(m_renderer);
            this->m_initialized = true;

            for (auto prop : this->m_input) {
                auto vtkprop = prop->getVtkObject();
                prop->linkViewer(this);

                if (vtkprop.GetPointer()) {
                    if (!this->m_renderer) {
                        return;
                    }

                    this->m_renderer->AddActor(vtkprop);
                }
            }

            this->update();
        }
        
        auto Viewer::update() -> void {
            if (!this->m_initialized) {
                return;
            }

            if (this->m_fboRenderer) {
                QQuickFramebufferObject::update();
            }
        }

        auto Viewer::removeData(quick::Vtk::Prop* prop) -> void {
        }

        auto Viewer::setHoverEnabled(bool hoverEnabled) -> void {
            this->m_hoverEnabled = hoverEnabled;

            setAcceptHoverEvents(hoverEnabled);

            emit this->hoverEnabledChanged();
        }

        auto Viewer::setMouseEnabled(bool mouseEnabled) -> void {
            this->m_mouseEnabled = mouseEnabled;

            if (mouseEnabled) {
                setAcceptedMouseButtons(Qt::AllButtons);
            }
            else {
                setAcceptedMouseButtons(Qt::NoButton);
            }

            emit this->mouseEnabledChanged();
        }

        auto Viewer::mousePressEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::mouseReleaseEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::mouseMoveEvent(QMouseEvent* event) -> void {
            if (this->m_fboRenderer) {
                this->m_fboRenderer->onMouseEvent(event);
            }
        }

        auto Viewer::hoverMoveEvent(QHoverEvent* event) -> void {
        }

        auto Viewer::createRenderer() const -> QQuickFramebufferObject::Renderer* {
            this->m_fboRenderer = new FboRenderer(static_cast<FboOffscreenWindow*>(m_win));

            return this->m_fboRenderer;
        }

        auto Viewer::GetRenderWindow() const -> vtkGenericOpenGLRenderWindow* {
            return m_win;
        }

        auto Viewer::getInput() -> QQmlListProperty<quick::Vtk::Prop> {
            return QQmlListProperty<quick::Vtk::Prop>(this, 0, &appendInput, &inputCount, &inputAt, &clearInputs);
        }

        auto Viewer::appendInput(QQmlListProperty<quick::Vtk::Prop>* list, quick::Vtk::Prop* prop) -> void {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if(viewer && prop) {
                viewer->m_input.append(prop);

                if (viewer->m_renderer) {
                    auto vtk_prop = prop->getVtkObject();

                    if (vtk_prop) {
                        viewer->m_renderer->AddActor(vtk_prop);
                    }
                }

                viewer->update();
            }

            emit viewer->inputChanged();
        }

        auto Viewer::inputCount(QQmlListProperty<Prop>* list) -> int {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                return viewer->m_input.count();
            }

            return 0;
        }

        auto Viewer::inputAt(QQmlListProperty<Prop>* list, int i) -> quick::Vtk::Prop* {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                return viewer->m_input.at(i);
            }

            return 0;
        }

        auto Viewer::clearInputs(QQmlListProperty<Prop>*list) -> void {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                viewer->m_input.clear();
                emit viewer->inputChanged();
            }
        }

        auto Viewer::getHoverEnabled() -> bool {
            return this->m_hoverEnabled;
        }

        auto Viewer::getMouseEnabled() -> bool {
            return this->m_mouseEnabled;
        }

        Viewer::~Viewer() {
            m_win->Delete();
        }
    }
}