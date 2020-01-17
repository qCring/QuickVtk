#include "quickVtkViewer.hpp"

#include "quickVtkProp.hpp"
#include "quickVtkFboRenderer.hpp"
#include "quickVtkAbstractWidget.hpp"
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

            for (auto object : this->m_input) {
                if (object->getType() == Object::Type::Prop) {
                    auto prop = reinterpret_cast<Prop*>(object);
                    prop->linkViewer(this);
                    this->m_renderer->AddActor(prop->getVtkObject());
                }
                else if (object->getType() == Object::Type::Widget) {
                    auto widget = reinterpret_cast<AbstractWidget*>(object);
                    auto vtkWidget = widget->getVtkObject();
                    vtkWidget->CreateDefaultRepresentation();
                    vtkWidget->SetInteractor(this->GetRenderWindow()->GetInteractor());
                    vtkWidget->SetManagesCursor(true);
                    vtkWidget->SetPickingManaged(true);
                    vtkWidget->On();
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

        auto Viewer::removeData(quick::Vtk::Object* object) -> void {
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
            
            this->forceActiveFocus();
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

        auto Viewer::getInput() -> QQmlListProperty<quick::Vtk::Object> {
            return QQmlListProperty<quick::Vtk::Object>(this, 0, &appendInput, &inputCount, &inputAt, &clearInputs);
        }

        auto Viewer::appendInput(QQmlListProperty<quick::Vtk::Object>* list, quick::Vtk::Object* object) -> void {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (object && viewer) {
                viewer->m_input.append(object);
            }

            if(viewer && viewer->m_renderer && object) {

                if (object->getType() == Object::Type::Prop) {
                    auto prop = reinterpret_cast<Prop*>(object);
                    viewer->m_renderer->AddActor(prop->getVtkObject());
                }
                else if (object->getType() == Object::Type::Widget) {
                    auto widget = reinterpret_cast<AbstractWidget*>(object);
                    auto vtkWidget = widget->getVtkObject();
                    vtkWidget->SetInteractor(viewer->GetRenderWindow()->GetInteractor());
                    vtkWidget->CreateDefaultRepresentation();
                    vtkWidget->On();
                }

                emit viewer->inputChanged();
                viewer->update();
            }
        }

        auto Viewer::inputCount(QQmlListProperty<Object>* list) -> int {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                return viewer->m_input.count();
            }

            return 0;
        }

        auto Viewer::inputAt(QQmlListProperty<Object>* list, int i) -> quick::Vtk::Object* {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                return viewer->m_input.at(i);
            }

            return 0;
        }

        auto Viewer::clearInputs(QQmlListProperty<Object>*list) -> void {
            auto viewer = qobject_cast<Viewer*>(list->object);

            if (viewer) {
                for (auto object : viewer->m_input) {
                    if (object->getType() == Object::Type::Prop) {
                        auto prop = reinterpret_cast<Prop*>(object);
                        viewer->m_renderer->RemoveActor(prop->getVtkObject());
                    }
                }

                viewer->m_input.clear();
                emit viewer->inputChanged();
                viewer->update();
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
