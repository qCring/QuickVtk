#pragma once

#include "quickQmlRegister.hpp"

#include <QQuickFramebufferObject>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProp.h>

class vtkGenericOpenGLRenderWindow;

namespace quick {

    namespace Vtk {

        class Prop;
        class FboRenderer;

        class Viewer : public QQuickFramebufferObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Vtk::Prop> input READ getInput NOTIFY inputChanged);
            Q_PROPERTY(bool hoverEnabled READ getHoverEnabled WRITE setHoverEnabled NOTIFY hoverEnabledChanged);
            Q_PROPERTY(bool mouseEnabled READ getMouseEnabled WRITE setMouseEnabled NOTIFY mouseEnabledChanged);
            Q_CLASSINFO("DefaultProperty", "input");
        private:
            friend class FboRenderer;
            QList<quick::Vtk::Prop*> m_input;
            bool m_initialized;
            bool m_hoverEnabled;
            bool m_mouseEnabled;
            vtkSmartPointer<vtkRenderer> m_renderer;
        public:
            static Qml::Register::VtkClass<Viewer> Register;
            Viewer();
            ~Viewer();
            Renderer *createRenderer() const override;
            vtkGenericOpenGLRenderWindow* GetRenderWindow() const;
        public:
            virtual auto init() -> void;
            auto update() -> void;
            auto removeData(quick::Vtk::Prop*) -> void;
            auto setHoverEnabled(bool) -> void;
            auto setMouseEnabled(bool) -> void;
            auto getInput() -> QQmlListProperty<quick::Vtk::Prop>;
            auto getHoverEnabled() -> bool;
            auto getMouseEnabled() -> bool;

            static auto appendInput(QQmlListProperty<quick::Vtk::Prop>*, quick::Vtk::Prop*) -> void;
            static auto inputCount(QQmlListProperty<quick::Vtk::Prop>*) -> int;
            static auto inputAt(QQmlListProperty<quick::Vtk::Prop>*, int) -> quick::Vtk::Prop*;
            static auto clearInputs(QQmlListProperty<quick::Vtk::Prop>*) -> void;
        protected:
            mutable FboRenderer* m_fboRenderer;
            vtkGenericOpenGLRenderWindow *m_win;
            auto updatePaintNode(QSGNode*, UpdatePaintNodeData*) -> QSGNode* override;
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
