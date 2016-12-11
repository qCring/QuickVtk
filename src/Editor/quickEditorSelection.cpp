#include "quickEditorSelection.hpp"

#include <QTextBlock>

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

                this->update();
            }
        }

        auto Selection::getStartPosition() -> int {
            return this->m_startPosition;
        }

        auto Selection::setEndPosition(int endPosition) -> void {
            if (this->m_endPosition != endPosition) {
                this->m_endPosition = endPosition;
                emit this->endPositionChanged();

                this->update();
            }
        }

        auto Selection::getEndPosition() -> int {
            return this->m_endPosition;
        }

        auto Selection::update() -> void {
            this->setEmpty(this->m_startPosition == this->m_endPosition);
            this->setStartLine(this->m_document->findBlock(this->m_startPosition).blockNumber());
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
