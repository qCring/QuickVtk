#include "quickCodeEditor.hpp"

#include "quickCodeHighlighter.hpp"
#include "quickCodeSelection.hpp"
#include "quickCodeFormatter.hpp"
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
            this->m_formatter = new Formatter();
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
            this->m_formatter->setTextDocument(editorDocument->textDocument());
        }

        auto Editor::setLine(int line) -> void {
            if (this->m_line != line) {
                this->m_line = line;
                emit this->lineChanged();
            }
        }

        auto Editor::getLine() -> int {
            return this->m_line;
        }

        auto Editor::setColumn(int column) -> void {
            if (this->m_column != column) {
                this->m_column = column;
                emit this->columnChanged();
            }
        }

        auto Editor::getColumn() -> int {
            return this->m_column;
        }

        auto Editor::setFilePath(const QString& filePath) -> void {
            this->m_filePath = filePath;
            emit this->filePathChanged();
        }

        auto Editor::getFilePath() -> QString {
            return this->m_filePath;
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

        auto Editor::onKeyPressed(int key, int modifiers, const QString& string) -> bool {
            return this->m_formatter->onKeyPressed(key, modifiers, string);
        }

        void Editor::format() {
            //TODO: text-formatting logic is bypassed atm

            /*
            QElapsedTimer timer;
            timer.start();

            this->m_formatter->format();

            this->m_formatTime = timer.elapsed();
            emit this->formatTimeChanged();*/
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
            if (IO::FileExists(filePath)) {
                this->m_filePath = filePath;
                emit this->filePathChanged();

                this->m_search->invalidate();
                this->setText(IO::Read::TextFromUrl(this->m_filePath));
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

        auto Editor::select(QTextCursor cursor) -> void {
            /*
            this->m_selection->setStartPosition(cursor.selectionStart());
            this->m_selection->setEndPosition(cursor.selectionEnd());

            emit this->m_selection->updateEditorSelection();*/
        }

        auto Editor::reset() -> void {
            this->m_formatter->reset();

            // auto cursor = this->getCurrentCursor();
            // cursor.setPosition(0);
            // this->select(cursor);

            this->setText("");
            this->setModified(false);

            Errors::instance->clear();
            this->m_search->invalidate();
        }

        void Editor::newFile() {
            this->m_filePath = "";
            emit this->filePathChanged();

            emit this->m_document->select(0, 0);
            this->reset();
        }

        auto Editor::getLines() -> QList<int> {
            return this->m_formatter->m_lines;
        }

        Editor::~Editor() {
            delete this->m_highlighter;
        }
    }
}
