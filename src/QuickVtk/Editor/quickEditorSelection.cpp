#include "quickEditorSelection.hpp"

#include <QTextBlock>
#include <QTextCursor>

namespace quick {

    namespace Editor {

        Selection* Selection::instance = nullptr;
        Qml::Register::Controller<Selection> Selection::Register;

        Selection::Selection() {
            if (instance) {
                throw "instance already existing";
            }
        }

        auto Selection::Create() -> void {
            instance = new Selection();
        }

        auto Selection::setDocument(QTextDocument* document) -> void {
            this->m_document = document;
        }

        auto Selection::setStartPosition(int startPosition) -> void {
            if (this->m_startPosition != startPosition) {
                this->m_startPosition = startPosition;
                emit this->startPositionChanged();

                auto cursor = QTextCursor(this->m_document);

                cursor.setPosition(this->m_startPosition);

                this->setStartColumn(cursor.columnNumber());
                this->setStartLine(cursor.blockNumber());

                this->setEmpty(this->m_startPosition == this->m_endPosition);
            }
        }

        auto Selection::getStartPosition() -> int {
            return this->m_startPosition;
        }

        auto Selection::setEndPosition(int endPosition) -> void {
            if (this->m_endPosition != endPosition) {
                this->m_endPosition = endPosition;
                emit this->endPositionChanged();

                auto cursor = QTextCursor(this->m_document);

                cursor.setPosition(this->m_endPosition);

                this->setEndColumn(cursor.columnNumber());
                this->setEndLine(cursor.blockNumber());

                this->setEmpty(this->m_startPosition == this->m_endPosition);
            }
        }

        auto Selection::getEndPosition() -> int {
            return this->m_endPosition;
        }

        auto Selection::setStartColumn(int startColumn) -> void {
            if (this->m_startColumn != startColumn) {
                this->m_startColumn = startColumn;
                emit this->startColumnChanged();
            }
        }

        auto Selection::getStartColumn() -> int {
            return this->m_startColumn;
        }

        auto Selection::setEndColumn(int endColumn) -> void {
            if (this->m_endColumn != endColumn) {
                this->m_endColumn = endColumn;
                emit this->endColumnChanged();
            }
        }

        auto Selection::getEndColumn() -> int {
            return this->m_endColumn;
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

        auto Selection::setEmpty(bool empty) -> void {
            if (this->m_empty != empty) {
                this->m_empty = empty;
                emit this->emptyChanged();
            }
        }

        auto Selection::isEmpty() -> bool {
            return this->m_empty;
        }
    }
}
