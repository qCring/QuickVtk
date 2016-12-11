#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QQuickTextDocument>

namespace quick {

    namespace Editor {

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
        public:
            static Controller* instance;
            static Qml::Register::Controller<Controller> Register;
            static auto Create() -> void;
        private:
            bool m_expanded = true;
            QQuickTextDocument* m_document;
        public:
            auto setDocument(QQuickTextDocument*) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto openFile(const QString&) -> void;
            auto getExpanded() -> bool;
            auto run() -> void;
            auto format() -> void;
            auto newFile() -> void;
            auto openFile() -> void;
            auto saveFile() -> void;
            auto saveFileAs() -> void;
            auto showSearch() -> void;
            auto resetFontSize() -> void;
            auto toggleExpanded() -> void;
            auto increaseFontSize() -> void;
            auto decreaseFontSize() -> void;
        signals:
            void documentChanged();
            void expandedChanged();
        };
    }
}
