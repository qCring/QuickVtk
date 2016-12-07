#include "quickCodeDocument.hpp"

#include "quickCodeEditor.hpp"
#include "quickCodeSelection.hpp"
#include "quickCodeUndoStack.hpp"

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
            this->m_undoStack = new UndoStack();
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
            if (key == Qt::Key_Escape || key == Qt::Key_Left || key == Qt::Key_Right || key == Qt::Key_Up || key == Qt::Key_Down) {
                return false;
            }

            if (modifiers & Qt::ControlModifier && modifiers & Qt::ShiftModifier && key == Qt::Key_Z) {
                return this->onRedo();
            }

            if (modifiers == Qt::ControlModifier) {
                switch (key) {
                    case Qt::Key_F: Editor::instance->showSearch(); return true;
                    case Qt::Key_A: return false;
                    case Qt::Key_C: return this->onCopy();
                    case Qt::Key_V: return this->onPaste();
                    case Qt::Key_Z: return this->onUndo();
                    case Qt::Key_X: return this->onCut();
                    default: break;
                }
            }

            switch (key) {
                case Qt::Key_Backspace: return this->onBackspace();
                case Qt::Key_Delete: return this->onDelete();
                default: return this->onChar(input);
            }
        }

        auto Document::format() -> void {
            std::cout << "format\n";
            return;
        }

        auto Document::clear() -> void {
            std::cout << "clear\n";

            auto selection = this->m_selection->getData();

            auto endCursor = selection.cursor;
            endCursor.select(QTextCursor::Document);

            this->select(0, endCursor.selectionEnd());

            selection = this->m_selection->getData();

            this->m_undoStack->pushUndo(Change::Delete(selection));

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

        auto Document::onChar(const QString& character) -> bool {
            if (character.isEmpty()) {
                return true;
            }

            auto selection = this->m_selection->getData();
            this->m_undoStack->pushUndo(Change::Insert(selection, character));
            selection.cursor.insertText(character);

            return true;
        }

        auto Document::onCopy() -> bool {
            std::cout << "copy\n";
            auto selection = this->m_selection->getData();

            QApplication::clipboard()->setText(selection.text);

            return true;
        }

        auto Document::onPaste() -> bool {
            auto selection = this->m_selection->getData();

            std::cout << "paste\n";
            auto text = QApplication::clipboard()->text();
            this->m_undoStack->pushUndo(Change::Insert(selection, text));
            selection.cursor.insertText(text);

            return true;
        }

        auto Document::onBackspace() -> bool {
            std::cout << "backspace\n";

            auto selection = this->m_selection->getData();

            if (selection.start != selection.end) {
                std::cout << "backspace: selection\n";

                this->m_undoStack->pushUndo(Change::Delete(selection));
                selection.cursor.deletePreviousChar();
            } else {
                if (selection.start > 0) {
                    std::cout << "backspace: prev character\n";

                    this->m_undoStack->pushUndo(Change(Change::Type::DeletePrevChar, selection.start - 1, selection.start - 1, "", characterAt(selection.start - 1)));
                    selection.cursor.deletePreviousChar();
                }
            }

            return true;
        }

        auto Document::onCut() -> bool {
            auto selection = this->m_selection->getData();

            std::cout << "cut\n";
            QApplication::clipboard()->setText(selection.text);
            this->m_undoStack->pushUndo(Change::Delete(selection));
            selection.cursor.removeSelectedText();

            return true;
        }

        auto Document::onDelete() -> bool {
            auto selection = this->m_selection->getData();

            if (selection.start != selection.end) {
                std::cout << "delete: selection\n";

                this->m_undoStack->pushUndo(Change::Delete(selection));
                selection.cursor.deleteChar();
            } else {
                auto endCursor = selection.cursor;
                endCursor.select(QTextCursor::Document);

                if (selection.start < endCursor.selectionEnd()) {
                    std::cout << "delete: next character\n";

                    this->m_undoStack->pushUndo(Change(Change::Type::DeleteNextChar, selection.start, selection.start, "", characterAt(selection.start)));
                    endCursor.select(QTextCursor::Document);
                    selection.cursor.deleteChar();
                }
            }

            return true;
        }

        auto Document::onUndo() -> bool {
            auto change = this->m_undoStack->popUndo();

            if (change.empty) {
                return true;
            }

            std::cout << "undo: " << change.toString() << "\n";

            auto selection = this->m_selection->getData();

            if (change.type == Change::Type::InsertText) {
                selection.cursor.setPosition(change.start);
                selection.cursor.setPosition(change.start + change.text.length(), QTextCursor::KeepAnchor);
                selection.cursor.insertText(change.selection);

                this->select(change.start, change.start + change.selection.length());
            } else if (change.type == Change::Type::DeletePrevChar || change.type == Change::Type::DeleteNextChar) {
                selection.cursor.setPosition(change.start);
                selection.cursor.insertText(change.text);

                if (change.type == Change::Type::DeletePrevChar) {
                    this->select(change.start + 1, change.start + 1);
                } else {
                    this->select(change.start, change.start);
                }
            } else if (change.type == Change::Type::DeleteText) {
                selection.cursor.setPosition(change.start);
                selection.cursor.insertText(change.selection);

                this->select(change.start, change.start + change.selection.length());
            }

            return true;
        }

        auto Document::onRedo() -> bool {
            std::cout << "redo\n";

            auto change = this->m_undoStack->popRedo();

            if (change.empty) {
                return true;
            }

            if (change.type == Change::Type::InsertText) {
                std::cout << "redo insert text\n";
            } else if (change.type == Change::Type::DeleteNextChar || change.type == Change::Type::DeletePrevChar) {
                std::cout << "redo delete char\n";
            } else if (change.type == Change::Type::DeleteText) {
                std::cout << "redo delete text\n";
            }

            return true;
        }

        Document::~Document() {
            delete this->m_undoStack;
            this->m_undoStack = nullptr;
        }
    }
}
