#include "quickCodeEditor.hpp"

#include "quickCodeHighlighter.hpp"
#include "quickCodeSelection.hpp"
#include "quickCodeCompiler.hpp"
#include "quickCodeSettings.hpp"
#include "quickCodeDocument.hpp"
#include "quickCodeErrors.hpp"
#include "quickCodeSearch.hpp"

#include "quickIO.hpp"

#include <iostream>
#include <QClipboard>
#include <QTextOption>
#include <QApplication>
#include <QElapsedTimer>
#include <QRegularExpression>

namespace quick {

    namespace Code {

        Editor* Editor::instance = nullptr;
        Qml::Register::Controller<Editor> Editor::Register;

        Editor::Editor() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            this->m_search = new Search();
            this->m_document = new Document();
            this->m_settings = new Settings();
        }

        auto Editor::Create() -> void {
            instance = new Editor();
        }

        auto Editor::showSearch() -> void {
            emit this->m_search->show();
        }

        auto Editor::setText(const QString& text) -> void {
            this->m_editorDocument->textDocument()->setPlainText(text);
        }

        auto Editor::getText() -> QString {
            return this->m_editorDocument->textDocument()->toPlainText();
        }

        auto Editor::getDocument() -> Document* {
            return this->m_document;
        }

        auto Editor::setEditorDocument(QQuickTextDocument* editorDocument) -> void {
            this->m_editorDocument = editorDocument;

            auto options = editorDocument->textDocument()->defaultTextOption();
            options.setTabStop(20);
            editorDocument->textDocument()->setDefaultTextOption(options);

            emit this->editorDocumentChanged();

            this->m_highlighter = new Highlighter(this);
            this->m_document->bindQTextDocument(editorDocument->textDocument());
        }

        auto Editor::getEditorDocument() -> QQuickTextDocument* {
            return this->m_editorDocument;
        }

        auto Editor::resetFontSize() -> void {
            this->setFontSize(12);
        }

        auto Editor::increaseFontSize() -> void {
            if (this->m_fontSize < this->maxFontSize) {
                this->setFontSize(this->m_fontSize + 2);
            }
        }

        auto Editor::decreaseFontSize() -> void {
            if (this->m_fontSize > this->minFontSize) {
                this->setFontSize(this->m_fontSize - 2);
            }
        }

        auto Editor::setFontSize(int fontSize) -> void {
            this->m_fontSize = fontSize;
            emit this->fontSizeChanged();
        }

        auto Editor::getFontSize() -> int {
            return this->m_fontSize;
        }

        auto Editor::setModified(bool modified) -> void {
            if (modified) {
                this->m_search->invalidate();
            }

            if (this->m_modified != modified) {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }

        auto Editor::getModified() -> bool {
            return this->m_modified;
        }

        auto Editor::getErrors() -> Errors* {
            return Errors::instance;
        }

        auto Editor::getSearch() -> Search* {
            return this->m_search;
        }

        auto Editor::getSettings() -> Settings* {
            return this->m_settings;
        }

        auto Editor::onKeyPressed(int key, int modifiers, const QString& input) -> bool {
            if (modifiers & Qt::ControlModifier && modifiers & Qt::ShiftModifier && key == Qt::Key_Z) {
                this->m_document->onRedo();
                return true;
            }

            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_F) {
                    this->showSearch();
                    return true;
                }

                if (key == Qt::Key_Z) {
                    this->m_document->onUndo();
                    return true;
                }

                if (key == Qt::Key_V) {
                    this->m_document->onPaste();
                    return true;
                }

                if (key == Qt::Key_A) {
                    return false;
                }
            }

            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                this->m_document->onEnter();
                return true;
            }

            if (key == Qt::Key_Escape) {
                this->m_document->onEscape();
                return true;
            }

            if (key == Qt::Key_Backspace) {
                this->m_document->onBackspace();
                return true;
            }

            if (key == Qt::Key_Backtab) {
                this->m_document->onBacktab();
                return true;
            }

            if (key == Qt::Key_Left || key == Qt::Key_Right || key == Qt::Key_Up || key == Qt::Key_Down) {
                return false;
            }

            return this->m_document->onCharacter(input);
        }

        void Editor::format() {
            if (this->m_document) {
                QElapsedTimer timer;
                timer.start();

                this->m_document->format();

                this->m_formatTime = timer.elapsed();
                emit this->formatTimeChanged();
            }
        }

        auto Editor::getFormatTime() -> int {
            return this->m_formatTime;
        }

        void Editor::run() {
            Code::Compiler::instance->setSource(this->getText());
        }

        void Editor::saveFile() {
            if (this->m_document) {
                this->m_document->save();
            }
        }

        auto Editor::open(const QString& filePath) -> void {
            /*if (this->m_document) {
                // check modified, save dialog then load new file
            } else {
                // if theres document, create a new one..
            }*/

            if (IO::FileExists(filePath)) {
                this->m_search->invalidate();
                this->setText(IO::Read::TextFromUrl(filePath));
                this->setModified(false);
                this->format();
                this->resetSelection();

                this->run();
            }
        }

        void Editor::toggleExpanded() {
            this->m_expanded =! this->m_expanded;
            emit this->expandedChanged();
        }

        auto Editor::getExpanded() -> bool {
            return this->m_expanded;
        }

        void Editor::openFile() {
            this->open(IO::FromDialog::SelectOpenFileUrl("*.qml"));
        }

        auto Editor::resetSelection() -> void {
            /*
            auto cursor = getCurrentCursor();
            cursor.setPosition(0);
            this->select(cursor);*/
        }

        auto Editor::reset() -> void {

            // auto cursor = this->getCurrentCursor();
            // cursor.setPosition(0);
            // this->select(cursor);

            this->setText("");
            this->setModified(false);

            Errors::instance->clear();
            this->m_search->invalidate();
        }

        void Editor::newFile() {
            this->m_document->clear();
            this->reset();
        }

        Editor::~Editor() {
            delete this->m_highlighter;
        }
    }
}
