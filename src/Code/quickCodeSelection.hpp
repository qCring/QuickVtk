#pragma once

#include "quickQmlRegister.hpp"

#include <QTextDocument>
#include <QTextCursor>
#include <QObject>

namespace quick {

    namespace Code {

        class Editor;

        class Selection : public QObject {
            Q_OBJECT
            Q_PROPERTY(int start READ getStart WRITE setStart NOTIFY startChanged);
            Q_PROPERTY(int end READ getEnd WRITE setEnd NOTIFY endChanged);
            Q_PROPERTY(int line READ getLine NOTIFY lineChanged);
            Q_PROPERTY(int column READ getColumn NOTIFY columnsChanged);
            Q_PROPERTY(int lines READ getLines NOTIFY linesChanged);
            Q_PROPERTY(int columns READ getColumns NOTIFY columnsChanged);
            Q_PROPERTY(bool empty READ getEmpty NOTIFY emptyChanged);
        public:
            struct Data {
                int start = 0;
                int end = 0;
                int line = 0;
                int lines = 0;
                bool empty = false;
                QString text;
                QTextCursor cursor;
            };
        private:
            friend class Editor;
            QTextDocument* m_textDocument = nullptr;
            bool m_empty = false;
            int m_start = 0;
            int m_end = 0;
            int m_line = 0;
            int m_lines = 0;
            int m_column = 0;
            int m_columns = 0;
        private:
            auto update() -> void;
        private:
            auto getCursor() -> QTextCursor;
            auto setStart(int) -> void;
            auto getStart() -> int;
            auto setEnd(int) -> void;
            auto getEnd() -> int;
            auto setLine(int) -> void;
            auto getLine() -> int;
            auto setLines(int) -> void;
            auto getLines() -> int;
            auto setColumn(int) -> void;
            auto getColumn() -> int;
            auto setColumns(int) -> void;
            auto getColumns() -> int;
            auto setEmpty(bool) -> void;
            auto getEmpty() -> bool;
        public:
            static Qml::Register::Type<Selection> Register;
            auto setTextDocument(QTextDocument*) -> void;
            auto getData() -> Data;
            auto clear() -> void;
        signals:
            void updateEditorSelection();
            void columnsChanged();
            void columnChanged();
            void linesChanged();
            void lineChanged();
            void startChanged();
            void endChanged();
            void emptyChanged();
        };
    }
}
