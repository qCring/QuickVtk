#pragma once

#include "quickQmlRegister.hpp"

#include <QTextDocument>
#include <QObject>

namespace quick {

    namespace Code {

        class Editor;

        class Selection : public QObject {
            Q_OBJECT
            Q_PROPERTY(int startPosition READ getStartPosition WRITE setStartPosition NOTIFY startPositionChanged);
            Q_PROPERTY(int endPosition READ getEndPosition WRITE setEndPosition NOTIFY endPositionChanged);
            Q_PROPERTY(int startLine READ getStartLine NOTIFY startLineChanged);
            Q_PROPERTY(int endLine READ getEndLine NOTIFY endLineChanged);
        private:
            friend class Editor;
            QTextDocument* m_document = nullptr;
            int m_startPosition = 0;
            int m_endPosition = 0;
            int m_startLine = 0;
            int m_endLine = 0;
        private:
            auto updateStartLine() -> void;
            auto updateEndLine() -> void;
            auto getCursor() -> QTextCursor;
        public:
            static Qml::Register::Type<Selection> Register;
            auto setDocument(QTextDocument*) -> void;
            auto setStartPosition(int) -> void;
            auto getStartPosition() -> int;
            auto setEndPosition(int) -> void;
            auto getEndPosition() -> int;
            auto setStartLine(int) -> void;
            auto getStartLine() -> int;
            auto setEndLine(int) -> void;
            auto getEndLine() -> int;
            auto isEmpty() -> bool;
            auto clear() -> void;
        signals:
            void updateEditorSelection();
            void startPositionChanged();
            void endPositionChanged();
            void startLineChanged();
            void endLineChanged();
        };
    }
}
