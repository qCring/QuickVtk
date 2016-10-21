#include "quickCodeSelection.hpp"

#include "quickCodeEditor.hpp"

#include <QTextBlock>

namespace quick {

    namespace Code {

        Qml::Register::Type<Selection> Selection::Register;

        auto Selection::setDocument(QTextDocument* document) -> void {
            this->m_document = document;
        }

        auto Selection::setStartPosition(int startPosition) -> void {
            if (this->m_startPosition != startPosition) {
                this->m_startPosition = startPosition;
                emit this->startLineChanged();

                this->updateStartLine();
            }
        }

        auto Selection::getStartPosition() -> int {
            return this->m_startPosition;
        }

        auto Selection::setEndPosition(int endPosition) -> void {
            if (this->m_endPosition != endPosition) {
                this->m_endPosition = endPosition;
                emit this->endPositionChanged();

                this->updateEndLine();
            }
        }

        auto Selection::getEndPosition() -> int {
            return this->m_endPosition;
        }

        auto Selection::getCursor() -> QTextCursor {
            if (!this->m_document) {
                return QTextCursor();
            }

            auto cursor = QTextCursor(this->m_document);

            cursor.setPosition(this->m_startPosition, QTextCursor::MoveAnchor);
            cursor.setPosition(this->m_endPosition, QTextCursor::KeepAnchor);

            return cursor;
        }

        auto Selection::updateStartLine() -> void {
            if (!this->m_document) {
                return;
            }

            this->setStartLine(this->m_document->findBlock(this->m_startPosition).blockNumber());
        }

        auto Selection::updateEndLine() -> void {
            if (!this->m_document) {
                return;
            }

            this->setEndLine(this->m_document->findBlock(this->m_endPosition).blockNumber());
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
