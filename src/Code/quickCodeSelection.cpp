#include "quickCodeSelection.hpp"

#include "quickCodeEditor.hpp"

#include <QTextBlock>
#include <iostream>

namespace quick {

    namespace Code {

        Qml::Register::Type<Selection> Selection::Register;

        auto Selection::setTextDocument(QTextDocument* textDocument) -> void {
            this->m_textDocument = textDocument;
        }

        auto Selection::getData() -> Data {
            auto data = Data();
            data.cursor = getCursor();
            data.start = this->m_start;
            data.end = this->m_end;
            data.line = this->m_line;
            data.lines = this->m_lines;
            data.empty = this->m_empty;
            data.text = data.cursor.selectedText();

            return data;
        }

        auto Selection::clear() -> void {
            /*
            auto cursor = this->getCursor();
            cursor.setPosition(Editor::instance->getEditorCursor());
            Editor::instance->select(cursor);*/
        }

        auto Selection::setStart(int start) -> void {
            std::cout << "Selection::setStart: " << start << std::endl;

            if (this->m_start != start) {
                this->m_start = start;
                emit this->startChanged();

                this->update();
            }
        }

        auto Selection::getStart() -> int {
            return this->m_start;
        }

        auto Selection::setEnd(int end) -> void {
            std::cout << "setEnd> " << end << std::endl;
            if (this->m_end != end) {
                this->m_end = end;
                emit this->endChanged();

                this->update();
            }
        }

        auto Selection::getEnd() -> int {
            return this->m_end;
        }

        auto Selection::setEmpty(bool empty) -> void {
            if (this->m_empty != empty) {
                this->m_empty = empty;
                emit this->emptyChanged();
            }
        }

        auto Selection::getEmpty() -> bool {
            return this->m_end == this->m_start;
        }

        auto Selection::getCursor() -> QTextCursor {
            if (!this->m_textDocument) {
                return QTextCursor();
            }

            auto cursor = QTextCursor(this->m_textDocument);

            cursor.setPosition(this->m_start, QTextCursor::MoveAnchor);
            cursor.setPosition(this->m_end, QTextCursor::KeepAnchor);

            return cursor;
        }

        auto Selection::update() -> void {
            if (!this->m_textDocument) {
                return;
            }

            this->setLine(this->m_textDocument->findBlock(this->m_start).blockNumber());
            this->setLines(this->m_textDocument->findBlock(this->m_end).blockNumber() - this->m_line);
            this->setEmpty(this->m_lines == 0);
        }

        auto Selection::setLine(int line) -> void {
            if (this->m_line != line) {
                this->m_line = line;
                emit this->lineChanged();
            }
        }

        auto Selection::getLine() -> int {
            return this->m_line;
        }

        auto Selection::setColumn(int column) -> void {
            if (this->m_column != column) {
                this->m_column = column;
                emit this->columnChanged();
            }
        }

        auto Selection::getColumn() -> int {
            return this->m_column;
        }

        auto Selection::setColumns(int columns) -> void {
            if (this->m_columns != columns) {
                this->m_columns = columns;
                emit this->columnsChanged();
            }
        }

        auto Selection::getColumns() -> int {
            return this->m_columns;
        }
            
        auto Selection::setLines(int lines) -> void {
            std::cout << "****** lines: " << lines << std::endl;
            if (this->m_lines != lines) {
                this->m_lines = lines;
                emit this->linesChanged();
            }
        }

        auto Selection::getLines() -> int {
            return this->m_lines;
        }
    }
}
