#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>
#include <QTextDocument>

namespace quick {

    namespace Editor {

        class Format;

        class Selection : public QObject {
            Q_OBJECT
            Q_PROPERTY(int startPosition READ getStartPosition WRITE setStartPosition NOTIFY startPositionChanged);
            Q_PROPERTY(int endPosition READ getEndPosition WRITE setEndPosition NOTIFY endPositionChanged);
            Q_PROPERTY(int startColumn READ getStartColumn NOTIFY startColumnChanged);
            Q_PROPERTY(int endColumn READ getEndColumn NOTIFY endColumnChanged);
            Q_PROPERTY(int startLine READ getStartLine NOTIFY startLineChanged);
            Q_PROPERTY(int endLine READ getEndLine NOTIFY endLineChanged);
            Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged);
        private:
            friend class Format;
            QTextDocument* m_document = nullptr;
            int m_startPosition = 0;
            int m_endPosition = 0;
            int m_startColumn = 0;
            int m_endColumn = 0;
            int m_startLine = 0;
            int m_endLine = 0;
            bool m_empty = true;
        public:
            static Qml::Register::Controller<Selection> Register;
            static auto Create() -> void;
            static Selection* instance;
        private:
            Selection();
            auto setEmpty(bool) -> void;
            auto setEndLine(int) -> void;
            auto setStartLine(int) -> void;
            auto setStartColumn(int) -> void;
            auto setEndColumn(int) -> void;
            auto getCursor(int) -> QTextCursor;
        public:
            auto setDocument(QTextDocument*) -> void;
            auto setStartPosition(int) -> void;
            auto getStartPosition() -> int;
            auto setEndPosition(int) -> void;
            auto getEndPosition() -> int;
            auto getStartColumn() -> int;
            auto getEndColumn() -> int;
            auto getStartLine() -> int;
            auto getEndLine() -> int;
            auto isEmpty() -> bool;
        signals:
            void startPositionChanged();
            void endPositionChanged();
            void startColumnChanged();
            void endColumnChanged();
            void startLineChanged();
            void endLineChanged();
            void emptyChanged();
        };
    }
}
