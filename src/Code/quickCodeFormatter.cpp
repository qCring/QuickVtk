#include "quickCodeFormatter.hpp"

#include "quickCodeAction.hpp"
#include "quickCodeEditor.hpp"
#include "quickCodeSelection.hpp"
#include "quickCodeDocument.hpp"

#include <QApplication>
#include <QTextCursor>
#include <QClipboard>
#include <QTextBlock>

#include <iostream>

namespace quick {

    namespace Code {

        Formatter::Formatter() {
            this->m_lines.append(0);
        }

        auto Formatter::setTextDocument(QTextDocument* document) -> void {
            this->m_document = document;
        }

        auto Formatter::invalidateText() -> void {
            Editor::instance->setModified(true);
        }

        auto Formatter::reset() -> void {
            this->m_lines.clear();
            this->m_lines.append(0);

            emit Editor::instance->linesChanged();
        }

        auto Formatter::handleBacktab() -> bool {
            this->insertText("<backtab>");
            return true;
        }

        auto Formatter::handleBackspace() -> bool {
            auto selection = Document::current->getSelection();
            auto cursor = selection->getCursor();
            auto startLine = selection->getStartLine();
            auto endLine = selection->getEndLine();

            if (cursor.position() < 1) {
                return true;
            }

            std::cout << "backspace [" << startLine << ":" << endLine << "]" << std::endl;

            if (selection->isEmpty()) {
                if (cursor.atBlockStart()) {
                    this->m_lines.removeAt(startLine);
                }

                //undoStack.push(Action::Deletion(this->m_document->characterAt(cursor.position()-1), cursor.position() - 1));
                undoStack.push(Action::Deletion(this->m_document->characterAt(cursor.position()-1), cursor.position()));
                cursor.deletePreviousChar();
            } else {
                undoStack.push(Action::Deletion(cursor.selectedText(), cursor.selectionStart()));
                cursor.insertBlock();

                for (auto i = startLine; i < endLine; i++) {
                    this->m_lines.removeAt(startLine);
                }
            }

            emit Editor::instance->linesChanged();
            
            this->invalidateText();
            
            return true;
        }

        auto Formatter::handleUndo() -> bool {
            auto cursor = Document::current->getSelection()->getCursor();

            std::cout << "handle undo - stack: " << this->undoStack.count() << " at cursor " << cursor.position() << std::endl;

            if (this->undoStack.count() > 0) {

                auto action = this->undoStack.pop()->getLast();
                this->redoStack.push(action);

                do {
                    if (action->type == Action::Type::Addition) {
                        std::cout << " undo prev addition by removing text at position: " << action->position << std::endl;
                        cursor.setPosition(action->position);
                        cursor.setPosition(action->position + action->text.length(), QTextCursor::KeepAnchor);
                        cursor.removeSelectedText();
                    } else {
                        std::cout << " undo prev deletion by adding text at position: " << action->position << std::endl;
                        cursor.setPosition(action->position);
                        cursor.insertText(action->text);
                    }

                    action = action->prev;
                } while (action);
            }

            return true;
        }

        auto Formatter::handleRedo() -> bool {
            auto cursor = Document::current->getSelection()->getCursor();

            std::cout << "handle redo - stack: " << this->redoStack.count() << " at cursor " << cursor.position() << std::endl;

            if (this->redoStack.count() > 0) {

                auto action = this->redoStack.pop();
                this->undoStack.push(action);

                do {
                    if (action->type == Action::Type::Addition) {
                        cursor.setPosition(action->position);
                        cursor.insertText(action->text);
                    } else {
                        cursor.setPosition(action->position);
                        cursor.setPosition(action->position + action->text.length(), QTextCursor::KeepAnchor);
                        cursor.removeSelectedText();
                    }

                    action = action->next;
                } while (action);
            }
            
            return true;
        }

        auto Formatter::handleShowSearch() -> bool {
            Editor::instance->showSearch();
            return true;
        }

        auto Formatter::handlePaste() -> bool {
            auto text = QApplication::clipboard()->text();

            insertText(text);
            return true;
        }

        auto Formatter::format() -> void {
        }

        auto Formatter::handleEscape() -> bool {
            auto selection = Document::current->getSelection();

            if (!selection->isEmpty()) {
                selection->clear();
            }

            return true;
        }

        auto Formatter::insertText(const QString& text) -> void {
            auto selection = Document::current->getSelection();
            auto cursor = selection->getCursor();
            auto startLine = selection->getStartLine();
            auto endLine = selection->getEndLine();

            if (selection->isEmpty()) {
                undoStack.push(Action::Addition(text, cursor.position()));
                cursor.insertText(text);
            } else {
                undoStack.push(Action::Deletion(cursor.selectedText(), cursor.selectionStart())->setNext(Action::Addition(text, selection->getStart())));
                cursor.insertText(text);

                for (auto i = startLine; i < endLine; i++) {
                    this->m_lines.removeAt(startLine);
                }
            }

            emit Editor::instance->linesChanged();
            this->invalidateText();
        }

        auto Formatter::handleEnter() -> bool {
            auto selection = Document::current->getSelection();
            auto cursor = selection->getCursor();
            auto startLine = selection->getStartLine();
            auto endLine = selection->getEndLine();

            std::cout << "enter [" << startLine << ":" << endLine << "]" << std::endl;

            if (selection->isEmpty()) {
                undoStack.push(Action::Addition("\n", cursor.position()));
                cursor.insertBlock();
                this->m_lines.insert(startLine + 1, this->m_lines.at(startLine) + 1);
            } else {
                undoStack.push(Action::Deletion(cursor.selectedText(), cursor.selectionStart())->setNext(Action::Addition(QString("\n").repeated(endLine - startLine + 1), selection->getStart())));
                cursor.insertBlock();

                for (auto i = startLine; i < endLine; i++) {
                    this->m_lines.removeAt(startLine);
                }

                this->m_lines.insert(startLine + 1, this->m_lines.at(startLine) + 1);
            }

            emit Editor::instance->linesChanged();

            this->invalidateText();

            return true;
        }

        auto Formatter::handleCloseBraces() -> bool {
            insertText("{");
            return true;
        }

        auto Formatter::onKeyPressed(int key, int modifiers, const QString& input) -> bool {
            if (modifiers & Qt::ControlModifier && modifiers & Qt::ShiftModifier && key == Qt::Key_Z) {
                return handleRedo();
            }

            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_F) {
                    return handleShowSearch();
                }

                if (key == Qt::Key_Z) {
                    return handleUndo();
                }

                if (key == Qt::Key_V) {
                    return handlePaste();
                }
            }

            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                return handleEnter();
            }

            if (input == "}") {
                return handleCloseBraces();
            }

            if (key == Qt::Key_Escape) {
                return this->handleEscape();
            }

            if (key == Qt::Key_Backspace) {
                return this->handleBackspace();
            }

            if (key == Qt::Key_Backtab) {
                return this->handleBacktab();
            }

            if (QRegularExpression("(\\w+)|(\\W+)").match(input).hasMatch()) {
                this->insertText(input);
                this->invalidateText();
                return true;
            }

            return false;
        }
    }
}
