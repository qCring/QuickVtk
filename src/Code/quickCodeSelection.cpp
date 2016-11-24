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
            data.startLine = this->m_endLine;
            data.endLine = this->m_endLine;
            data.empty = isEmpty();
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

                this->updateStartLine();
            }
        }

        auto Selection::getStart() -> int {
            return this->m_start;
        }

        auto Selection::setEnd(int end) -> void {
            if (this->m_end != end) {
                this->m_end = end;
                emit this->endChanged();

                this->updateEndLine();
            }
        }

        auto Selection::getEnd() -> int {
            return this->m_end;
        }

        auto Selection::isEmpty() -> bool {
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

        auto Selection::updateStartLine() -> void {
            if (!this->m_textDocument) {
                return;
            }

            this->setStartLine(this->m_textDocument->findBlock(this->m_start).blockNumber());
        }

        auto Selection::updateEndLine() -> void {
            if (!this->m_textDocument) {
                return;
            }

            this->setEndLine(this->m_textDocument->findBlock(this->m_end).blockNumber());
        }

        auto Selection::setStartLine(int startLine) -> void {
            if (this->m_startLine != startLine) {
                this->m_startLine = startLine;
                emit this->startLineChanged();
            }
        }

        auto Selection::getStartLine() -> int {
            return this->m_startLine;
        }

        auto Selection::setEndLine(int endLine) -> void {
            if (this->m_endLine != endLine) {
                this->m_endLine = endLine;
                emit this->endLineChanged();
            }
        }

        auto Selection::getEndLine() -> int {
            return this->m_endLine;
        }
    }
}
