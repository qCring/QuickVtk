#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QQuickTextDocument>

namespace quick {

    namespace Editor {

        class Search;
        class Selection;

        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(int fontSize READ getFontSize NOTIFY fontSizeChanged);
            Q_PROPERTY(bool expanded READ getExpanded NOTIFY expandedChanged);
            Q_PROPERTY(QQuickTextDocument* document READ getDocument WRITE setDocument NOTIFY documentChanged);
            Q_PROPERTY(quick::Editor::Search* search READ getSearch CONSTANT);
            Q_PROPERTY(quick::Editor::Selection* selection READ getSelection CONSTANT);
        public:
            static Controller* instance;
            static Qml::Register::Controller<Controller> Register;
            static auto Create() -> void;
        private:
            int m_fontSizeMin = 8;
            int m_fontSize = 11;
            int m_fontSizeMax = 20;
            bool m_expanded = true;
            QQuickTextDocument* m_document;
        public:
            auto setDocument(QQuickTextDocument*) -> void;
            auto getDocument() -> QQuickTextDocument*;
            auto getSelection() -> Selection*;
            auto getSearch() -> Search*;
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
            auto getFontSize() -> int;
        signals:
            void fontSizeChanged();
            void documentChanged();
            void expandedChanged();
            void compile();
        };
    }
}
