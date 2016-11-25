#include "quickCodeDocument.hpp"

#include "quickCodeEditor.hpp"
#include "quickCodeAction.hpp"
#include "quickCodeSelection.hpp"

#include "quickIO.hpp"

#include <QApplication>
#include <QClipboard>
#include <iostream>

namespace quick {

    namespace Code {

        Document* Document::current = nullptr;
        Qml::Register::Type<Document> Document::Register;

        Document::Document() {
            this->m_selection = new Selection();
            this->m_lines.clear();
            this->m_lines.append(0);
        }

        auto Document::bindQTextDocument(QTextDocument* document) -> void {
            this->m_document = document;
            this->m_selection->setTextDocument(document);

            if (document == nullptr) {
                this->disconnect(document, &QTextDocument::modificationChanged, this, &Document::onModified);
            } else {
                Document::current = this;
                this->connect(document, &QTextDocument::modificationChanged, this, &Document::onModified);
            }
        }

        auto Document::format() -> void {
            return;
        }

        auto Document::clear() -> void {
            if (this->m_document) {
                emit this->select(0, 0);
                this->m_document->setPlainText("");
                this->m_lines.clear();
                this->m_lines.append(0);
            }
        }

        void Document::onModified(bool modified) {
            if (this->m_modified != modified) {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }

        auto Document::getSelection() -> Selection* {
            return this->m_selection;
        }
        
        auto Document::getModified() -> bool {
            return this->m_modified;
        }

        auto Document::getFileUrl() -> const QString {
            return this->m_fileUrl;
        }

        auto Document::saveAs() -> void {
            auto newPath = IO::FromDialog::SelectSaveFileUrl();

            if (newPath.isNull() || newPath.isEmpty()) {
                return;
            }

            if (Document::current == this) {
                this->m_text = this->m_document->toPlainText();
            }

            if (IO::Write::TextToFile(this->m_text, newPath)) {
                this->m_document->setModified(false);
                this->m_fileUrl = newPath;
                emit this->fileUrlChanged();
            }
        }

        auto Document::save() -> void {
            if (this->m_fileUrl.length() > 0 && IO::FileExists(this->m_fileUrl)) {
                if (this->m_modified) {

                    if (Document::current == this) {
                        this->m_text = this->m_document->toPlainText();
                    }

                    IO::Write::TextToFile(this->m_document->toPlainText(), this->m_fileUrl);
                    this->m_document->setModified(false);
                }
            } else {
                this->saveAs();
            }
        }

        auto Document::characterAt(int position) -> QString {
            return this->m_document->characterAt(position);
        }

        auto Document::getLines() -> QList<int> {
            return this->m_lines;
        }

        auto Document::onCut() -> void {
            return;
        }

        auto Document::onPaste() -> void {
            auto text = QApplication::clipboard()->text();
            auto selection = this->m_selection->getData();

            selection.cursor.insertText(text);
            
            return;
        }

        auto Document::onEnter() -> void {
            auto selection = this->m_selection->getData();
            auto cursor = selection.cursor;

            if (selection.empty) {
                this->m_undoStack.push(Action::Addition("\n", selection.start));
                cursor.insertBlock();
                this->m_lines.insert(selection.line + 1, this->m_lines.at(selection.line) + 1);
                emit this->linesChanged();
            } else {
                this->m_undoStack.push(Action::Deletion(selection.text, selection.start)->setNext(Action::Addition(QString("\n").repeated(selection.lines + 1), selection.start)));

                cursor.insertBlock();

                for (auto i = 0; i < selection.lines; i++) {
                    this->m_lines.removeAt(selection.line);
                }

                this->m_lines.insert(selection.line + 1, this->m_lines.at(selection.line) + 1);

                emit this->linesChanged();
            }
        }

        auto Document::onEscape() -> void {
            return;
        }

        auto Document::onBacktab() -> void {
            return;
        }

        auto Document::onBackspace() -> void {
            auto selection = this->m_selection->getData();

            if (selection.empty) {
                if (selection.start < 1) {
                    return;
                }

                if (selection.cursor.atBlockStart()) {
                    this->m_lines.removeAt(selection.line);
                    emit this->linesChanged();
                }

                this->m_undoStack.push(Action::Deletion(characterAt(selection.start - 1), selection.start));
                selection.cursor.deletePreviousChar();
            } else {
                this->m_undoStack.push(Action::Deletion(selection.text, selection.start));
                selection.cursor.insertBlock();

                for (auto i = 0; i < selection.lines; i++) {
                    this->m_lines.removeAt(selection.line);
                }

                emit this->linesChanged();
            }
        }

        auto Document::onCharacter(const QString& text) -> bool {
            auto selection = this->m_selection->getData();

            if (selection.empty) {
                this->m_undoStack.push(Action::Addition(text, selection.start));
                selection.cursor.insertText(text);
            } else {
                this->m_undoStack.push(Action::Deletion(selection.text, selection.start)->setNext(Action::Addition(text, selection.start)));
                selection.cursor.insertText(text);

                for (auto i = 0; i < selection.lines; i++) {
                    this->m_lines.removeAt(selection.line);
                }

                emit this->linesChanged();
            }

            return true;
        }

        auto Document::onUndo() -> void {
            auto selection = this->m_selection->getData();
            auto cursor = selection.cursor;

            if (this->m_undoStack.count() > 0) {

                auto action = this->m_undoStack.pop()->getLast();
                this->m_redoStack.push(action);

                do {
                    if (action->type == Action::Type::Addition) {
                        cursor.setPosition(action->position);
                        cursor.setPosition(action->position + action->text.length(), QTextCursor::KeepAnchor);
                        cursor.removeSelectedText();
                    } else {
                        cursor.setPosition(action->position);
                        cursor.insertText(action->text);
                    }

                    action = action->prev;
                } while (action);
            }
        }

        auto Document::onRedo() -> void {
            auto selection = this->m_selection->getData();
            auto cursor = selection.cursor;

            if (this->m_redoStack.count() > 0) {

                auto action = this->m_redoStack.pop();
                this->m_undoStack.push(action);

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
        }
    }
}
