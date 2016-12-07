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
            if (modifiers & Qt::ControlModifier && modifiers & Qt::ShiftModifier && key == Qt::Key_Z) {
                this->onRedo();
                return true;
            }

            if (key == Qt::Key_Escape || key == Qt::Key_Left || key == Qt::Key_Right || key == Qt::Key_Up || key == Qt::Key_Down) {
                return false;
            }

            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_F) {
                    Editor::instance->showSearch();
                    return true;
                }

                if (key == Qt::Key_A) {
                    return false;
                }
            }

            auto selection = this->m_selection->getData();

            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_Z) {
                    auto change = this->m_undoStack->popUndo();

                    if (change.empty) {
                        return true;
                    }

                    std::cout << "undo: " << change.toString() << "\n";

                    selection.cursor.setPosition(change.start);
                    selection.cursor.setPosition(change.start + change.text.length(), QTextCursor::KeepAnchor);
                    selection.cursor.insertText(change.selection);

                    this->select(change.start, change.start + change.selection.length());

                    return true;
                }

                if (key == Qt::Key_V) {
                    std::cout << "paste\n";
                    auto text = QApplication::clipboard()->text();
                    this->m_undoStack->pushUndo(Change::Insert(selection, text));
                    selection.cursor.insertText(text);
                    
                    return true;
                }
            }

            if (key == Qt::Key_Backspace) {
                return false;
            }

            if (input.isEmpty()) {
                return true;
            }

            this->m_undoStack->pushUndo(Change::Insert(selection, input));

            selection.cursor.insertText(input);

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
            //selection.cursor.setPosition(0, QTextCursor::KeepAnchor);

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

        auto Document::onUndo() -> void {
            std::cout << "undo\n";
        }

        auto Document::onRedo() -> void {
            std::cout << "redo\n";
        }

        Document::~Document() {
            delete this->m_undoStack;
            this->m_undoStack = nullptr;
        }
    }
}
