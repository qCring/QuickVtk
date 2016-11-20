#include "quickCodeEditor.hpp"

#include "quickCodeHighlighter.hpp"
#include "quickCodeSelection.hpp"
#include "quickCodeFormatter.hpp"
#include "quickCodeCompiler.hpp"
#include "quickCodeSettings.hpp"
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
            this->m_formatter = new Formatter();
            this->m_selection = new Selection();
            this->m_settings = new Settings();
            this->m_lines.append(0);
        }

        auto Editor::Create() -> void {
            instance = new Editor();
        }

        auto Editor::showSearch() -> void {
            emit this->m_search->show();
        }

        auto Editor::setText(const QString& text) -> void {
            this->m_document->textDocument()->setPlainText(text);
        }

        auto Editor::getText() -> QString {
            return this->m_document->textDocument()->toPlainText();
        }

        auto Editor::setDocument(QQuickTextDocument* document) -> void {
            this->m_document = document;

            auto options = document->textDocument()->defaultTextOption();
            options.setTabStop(20);
            document->textDocument()->setDefaultTextOption(options);

            emit this->documentChanged();

            this->m_highlighter = new Highlighter(this);
            this->m_formatter->setTextDocument(this->m_document->textDocument());
            this->m_selection->setDocument(this->m_document->textDocument());
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

        auto Editor::getDocument() -> QQuickTextDocument* {
            return this->m_document;
        }

        auto Editor::getCurrentCursor() -> QTextCursor {
            auto c = QTextCursor(this->m_document->textDocument());

            c.setPosition(this->m_selection->getStartPosition(), QTextCursor::MoveAnchor);
            c.setPosition(this->m_selection->getEndPosition(), QTextCursor::KeepAnchor);

            return c;
        }

        auto Editor::setEditorCursor(int position) -> void {
            this->m_editorCursor = position;

            emit this->editorCursorChanged();
        }

        auto Editor::getEditorCursor() -> int {
            return this->m_editorCursor;
        }

        void Editor::increaseFontSize() {
            if (this->m_fontSize < this->maxFontSize) {
                this->setFontSize(this->m_fontSize + 2);
            }
        }

        void Editor::decreaseFontSize() {
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

        auto Editor::getSelection() -> Selection* {
            return this->m_selection;
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
            if (this->m_filePath.length() > 0 && IO::FileExists(this->m_filePath)) {
                IO::Write::TextToFile(this->getText(), this->m_filePath);
                this->setModified(false);
            } else {
                auto newPath = IO::FromDialog::SelectSaveFileUrl();

                if (newPath.isNull() || newPath.isEmpty()) {
                    return;
                }

                if (IO::Write::TextToFile(this->getText(), newPath)) {
                    this->setModified(false);

                    this->m_filePath = newPath;
                    emit this->filePathChanged();
                }
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

        void Editor::openFile() {
            this->open(IO::FromDialog::SelectOpenFileUrl("*.qml"));
        }

        auto Editor::resetSelection() -> void {
            auto cursor = getCurrentCursor();
            cursor.setPosition(0);
            this->select(cursor);
        }

        auto Editor::select(QTextCursor cursor) -> void {
            this->m_selection->setStartPosition(cursor.selectionStart());
            this->m_selection->setEndPosition(cursor.selectionEnd());

            emit this->m_selection->updateEditorSelection();
        }

        void Editor::newFile() {
            this->m_filePath = "";
            emit this->filePathChanged();

            auto cursor = this->getCurrentCursor();
            cursor.setPosition(0);
            this->select(cursor);
            
            this->setText("");
            this->setModified(false);

            this->m_lines.clear();
            emit this->linesChanged();

            Errors::instance->clear();
            this->m_search->invalidate();
        }

        auto Editor::setLines(QList<int> lines) -> void {
            this->m_lines = lines;
            emit this->linesChanged();
        }

        auto Editor::getLines() -> QList<int> {
            return this->m_lines;
        }

        Editor::~Editor() {
            delete this->m_highlighter;
        }
    }
}
