#pragma once

#include "quickQmlRegister.hpp"

#include <QQuickFramebufferObject>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProp.h>

class vtkGenericOpenGLRenderWindow;

namespace quick {

    namespace Vtk {

        class Object;
        class FboRenderer;

        class Viewer : public QQuickFramebufferObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Vtk::Object> input READ getInput NOTIFY inputChanged);
            Q_PROPERTY(bool hoverEnabled READ getHoverEnabled WRITE setHoverEnabled NOTIFY hoverEnabledChanged);
            Q_PROPERTY(bool mouseEnabled READ getMouseEnabled WRITE setMouseEnabled NOTIFY mouseEnabledChanged);
            Q_CLASSINFO("DefaultProperty", "input");
        private:
            friend class FboRenderer;
            QList<quick::Vtk::Object*> m_input;
            bool m_initialized = false;
            bool m_hoverEnabled = false;
            bool m_mouseEnabled = false;
            vtkSmartPointer<vtkRenderer> m_renderer;
        public:
            static Qml::Register::Class<Viewer> Register;
            Viewer();
            ~Viewer();
            Renderer *createRenderer() const override;
            vtkGenericOpenGLRenderWindow* GetRenderWindow() const;
        public:
            virtual auto init() -> void;
            auto update() -> void;
            auto removeData(quick::Vtk::Object*) -> void;
            auto setHoverEnabled(bool) -> void;
            auto setMouseEnabled(bool) -> void;
            auto getInput() -> QQmlListProperty<quick::Vtk::Object>;
            auto getHoverEnabled() -> bool;
            auto getMouseEnabled() -> bool;

            static auto appendInput(QQmlListProperty<quick::Vtk::Object>*, quick::Vtk::Object*) -> void;
            static auto inputCount(QQmlListProperty<quick::Vtk::Object>*) -> int;
            static auto inputAt(QQmlListProperty<quick::Vtk::Object>*, int) -> quick::Vtk::Object*;
            static auto clearInputs(QQmlListProperty<quick::Vtk::Object>*) -> void;
        protected:
            mutable FboRenderer* m_fboRenderer;
            vtkGenericOpenGLRenderWindow *m_win;
            auto mousePressEvent(QMouseEvent*) -> void override;
            auto mouseReleaseEvent(QMouseEvent*) -> void override;
            auto mouseMoveEvent(QMouseEvent*) -> void override;
            auto hoverMoveEvent(QHoverEvent*) -> void override;
        signals:
            void inputChanged();
            void hoverEnabledChanged();
            void mouseEnabledChanged();
        };
    }
}
