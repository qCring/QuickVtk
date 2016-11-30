#include "quickCodeDocument.hpp"

#include "quickCodeEditor.hpp"
#include "quickCodeAction.hpp"
#include "quickCodeSelection.hpp"

#include "quickIO.hpp"

#include <QApplication>
#include <QClipboard>
#include <QTextBlock>

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

        auto Document::onKey(int key, int modifiers, const QString& input) -> bool {
            if (modifiers & Qt::ControlModifier && modifiers & Qt::ShiftModifier && key == Qt::Key_Z) {
                this->onRedo();
                return true;
            }

            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_F) {
                    Editor::instance->showSearch();
                    return true;
                }

                if (key == Qt::Key_Z) {
                    this->onUndo();
                    return true;
                }

                if (key == Qt::Key_V) {
                    this->onPaste();
                    return true;
                }

                if (key == Qt::Key_A) {
                    return false;
                }
            }

            if (key == Qt::Key_Escape) {
                return false;
            }

            if (key == Qt::Key_Left || key == Qt::Key_Right || key == Qt::Key_Up || key == Qt::Key_Down) {
                return false;
            }

            bool isNewline = false;
            bool isBackspace = false;
            bool isDelete = false;

            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                isNewline = true;
            } else if (key == Qt::Key_Backspace) {
                isBackspace = true;
            } else if (key == Qt::Key_Delete) {
                isDelete = true;
            }

            if (!isBackspace && !isDelete && !isNewline && input.isEmpty()) {
                return true;
            }

            auto selection = this->m_selection->getData();
            Action* deleteAction = nullptr;

            if (!selection.empty) {
                deleteAction = Action::DeleteSelection(selection);
            }

            if (isBackspace) {
                if (selection.start < 1) {
                    return true;
                }

                Action::DeletePreviousChar(selection, characterAt(selection.start - 1), deleteAction);
                selection.cursor.deletePreviousChar();
            } else if (isDelete) {
                auto endCursor = selection.cursor;
                endCursor.select(QTextCursor::Document);

                if (selection.start >= endCursor.selectionEnd()) {
                    return true;
                }

                Action::DeleteNextChar(selection.start, characterAt(selection.start), deleteAction);
                selection.cursor.deleteChar();
            } else if (isNewline) {
                Action::InsertNewline(selection, deleteAction);
                selection.cursor.insertBlock();
            } else {
                std::cout << "handle char: " + input.toStdString() + "\n";
                Action::InsertChar(selection, input.at(0), deleteAction);
                selection.cursor.insertText(input);
            }

            return true;
        }

        auto Document::format() -> void {
            std::cout << "format\n";
            return;
        }

        auto Document::clear() -> void {
            std::cout << "clear\n";
            auto selection = this->m_selection->getData();
            selection.cursor.select(QTextCursor::Document);
            selection.cursor.removeSelectedText();
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

        auto Document::characterAt(int position) -> QChar {
            return this->m_document->characterAt(position);
        }

        auto Document::getLines() -> QList<int> {
            return this->m_lines;
        }

        auto Document::onCopy() -> void {
            std::cout << "copy\n";
            auto selection = this->m_selection->getData();

            QApplication::clipboard()->setText(selection.text);
        }

        auto Document::onCut() -> void {
            std::cout << "cut\n";
            auto selection = this->m_selection->getData();

            QApplication::clipboard()->setText(selection.text);
            selection.cursor.removeSelectedText();

            return;
        }

        auto Document::onPaste() -> void {
            std::cout << "paste\n";

            auto text = QApplication::clipboard()->text();
            auto selection = this->m_selection->getData();

            selection.cursor.insertText(text);
            return;
        }

        auto Document::onEnter() -> void {
            std::cout << "enter\n";
        }

        auto Document::onEscape() -> void {
            std::cout << "escape\n";
            return;
        }

        auto Document::onBacktab() -> void {
            std::cout << "backtab\n";
            return;
        }

        auto Document::onBackspace() -> void {
            std::cout << "backspace\n";
        }

        auto Document::onCharacter(const QString& text) -> bool {
            std::cout << "char\n";
            return true;
        }

        auto Document::onUndo() -> void {
            std::cout << "undo\n";
        }

        auto Document::onRedo() -> void {
            std::cout << "redo\n";
        }
    }
}
