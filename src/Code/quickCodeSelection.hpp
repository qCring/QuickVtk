#pragma once

#include "quickQmlRegister.hpp"

#include <QTextDocument>
#include <QObject>

namespace quick {

    namespace Code {

        class Editor;

        class Selection : public QObject {
            Q_OBJECT
            Q_PROPERTY(int start READ getStart WRITE setStart NOTIFY startChanged);
            Q_PROPERTY(int end READ getEnd WRITE setEnd NOTIFY endChanged);
            Q_PROPERTY(int startLine READ getStartLine NOTIFY startLineChanged);
            Q_PROPERTY(int endLine READ getEndLine NOTIFY endLineChanged);
        private:
            friend class Editor;
            QTextDocument* m_textDocument = nullptr;
            int m_start = 0;
            int m_end = 0;
            int m_startLine = 0;
            int m_endLine = 0;
        private:
            auto updateStartLine() -> void;
            auto updateEndLine() -> void;
        public:
            static Qml::Register::Type<Selection> Register;
            auto setTextDocument(QTextDocument*) -> void;
            auto getCursor() -> QTextCursor;
            auto setStart(int) -> void;
            auto getStart() -> int;
            auto setEnd(int) -> void;
            auto getEnd() -> int;
            auto setStartLine(int) -> void;
            auto getStartLine() -> int;
            auto setEndLine(int) -> void;
            auto getEndLine() -> int;
            auto isEmpty() -> bool;
            auto clear() -> void;
        signals:
            void updateEditorSelection();
            void startLineChanged();
            void endLineChanged();
            void startChanged();
            void endChanged();
        };
    }
}
