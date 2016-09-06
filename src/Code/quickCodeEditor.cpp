#include "quickCodeEditor.hpp"
#include "quickCodeHighlighter.hpp"
#include "quickCodeCompiler.hpp"
#include "quickCodeIssues.hpp"
#include "quickIO.hpp"

#include <QTextOption>
#include <QApplication>
#include <QClipboard>
#include <QRegularExpression>
#include <iostream>

namespace quick {

    namespace Code {

        Editor* Editor::instance = nullptr;
        Qml::Register::Controller<Editor> Editor::Register;

        Editor::Editor() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }

            this->m_highlighter     = nullptr;
            this->m_selectionStart  = 0;
            this->m_selectionEnd    = 0;
            this->m_editorCursor    = 0;
            this->m_line            = 0;
            this->m_column          = 0;
        }

        auto Editor::Create() -> void {
            instance = new Editor();
        }

        auto Editor::GetInstance() -> Editor* {
            return instance;
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

        auto Editor::setSelectionStart(int pos) -> void {
            this->m_selectionStart = pos;

            emit this->selectionStartChanged();
        }

        auto Editor::setSelectionEnd(int pos) -> void {
            this->m_selectionEnd = pos;

            emit this->selectionEndChanged();

            auto cursor = getCurrentCursor();
            cursor.setPosition(pos);
            this->setLine(cursor.blockNumber());
            this->setColumn(cursor.columnNumber());
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

        auto Editor::getSelectionStart() -> int {
            return this->m_selectionStart;
        }

        auto Editor::getSelectionEnd() -> int {
            return this->m_selectionEnd;
        }

        auto Editor::getCurrentCursor() -> QTextCursor {
            auto c = QTextCursor(this->m_document->textDocument());

            c.setPosition(this->m_selectionEnd, QTextCursor::MoveAnchor);
            c.setPosition(this->m_selectionStart, QTextCursor::KeepAnchor);

            return c;
        }

        auto Editor::setEditorCursor(int position) -> void {
            this->m_editorCursor = position;

            emit this->editorCursorChanged();
        }

        auto Editor::getEditorCursor() -> int {
            return this->m_editorCursor;
        }

        auto Editor::setFontSize(int fontSize) -> void {
            this->m_fontSize = fontSize;
            emit this->fontSizeChanged();
        }

        auto Editor::getFontSize() -> int {
            return this->m_fontSize;
        }

        auto Editor::setModified(bool modified) -> void {
            if (this->m_modified != modified) {
                this->m_modified = modified;
                emit this->modifiedChanged();
            }
        }

        auto Editor::getModified() -> bool {
            return this->m_modified;
        }

        auto Editor::getIssues() -> Issues* {
            return Issues::instance;
        }

        auto Editor::onKeyPressed(int key, int modifiers, const QString& string) -> bool {
            if (modifiers == Qt::ControlModifier) {
                if (key == Qt::Key_Plus && this->m_fontSize < this->maxFontSize) {
                    this->setFontSize(this->m_fontSize + 2);
                    return true;
                }

                if (key == Qt::Key_Minus && this->m_fontSize > this->minFontSize) {
                    this->setFontSize(this->m_fontSize - 2);
                    return true;
                }

                if (key == Qt::Key_S) {
                    this->saveFile();
                    return true;
                }

                if (key == Qt::Key_R) {
                    this->run();
                    return true;
                }

                if (key == Qt::Key_O) {
                    this->openFile();
                    return true;
                }

                if (key == Qt::Key_N) {
                    this->newFile();
                    return true;
                }

                if (key == Qt::Key_I) {
                    this->format();
                    return true;
                }

                if (key == Qt::Key_V) {
                    auto text = QApplication::clipboard()->text();

                    if (!text.isEmpty())
                    {
                        auto cursor = this->getCurrentCursor();
                        cursor.beginEditBlock();
                        cursor.insertText(text);
                        cursor.endEditBlock();

                        this->setModified(true);
                    }
                    return true;
                }
            }

            if (key == Qt::Key_Return || key == Qt::Key_Enter) {
                auto cursor = this->getCurrentCursor();
                cursor.beginEditBlock();

                auto block = cursor.block();
                auto line = block.text();
                auto left = line.left(cursor.positionInBlock());
                auto right = line.right(line.length() - cursor.positionInBlock());

                auto currentLevel = 0;
                auto newLevel = 0;
                auto open = left.contains("{");
                auto close = left.contains("}");

                if (open || !close) {

                    if (block.blockNumber() > 0) {
                        auto prevLevel = block.previous().userState();
                        prevLevel += prevLevel % 2;
                        currentLevel = prevLevel;
                    }

                    currentLevel += open;
                    newLevel = currentLevel + open;

                    cursor.block().setUserState(currentLevel);
                    cursor.insertBlock();

                    cursor.block().setUserState(newLevel);

                    for (auto i = 0; i < newLevel / 2; i++) {
                        cursor.insertText("\t");
                    }
                }

                else {
                    cursor.insertBlock();
                    auto level = block.userState();

                    for (auto i = 0; i < level / 2; i++) {
                        cursor.insertText("\t");
                    }
                }

                cursor.endEditBlock();
                this->setModified(true);

                return true;
            }

            if (string == "}") {
                auto cursor = this->getCurrentCursor();
                auto text = cursor.block().text();
                auto block = cursor.block();
                auto line = block.text();
                auto left = line.left(cursor.positionInBlock());
                auto right = line.right(line.length() - cursor.positionInBlock());

                auto level = 0;

                if (QRegularExpression("\\w+").match(left).hasMatch()) {
                    cursor.insertText("}");
                    return true;
                } else {
                    level = std::max(block.userState() - 2, 0);
                    block.setUserState(level);
                }

                cursor.select(QTextCursor::LineUnderCursor);

                for (auto i = 0; i < level/2; ++i) {
                    cursor.insertText("\t");
                }

                cursor.insertText("}" + right);

                return true;
            }

            if (QRegularExpression("(\\w+)|(\\W+)").match(string).hasMatch())
            {
                this->setModified(true);
            }

            return false;
        }

        void Editor::format() {
            auto block = this->m_document->textDocument()->firstBlock();

            do {
                auto line = block.text().simplified();
                auto open = line.contains("{");
                auto close = line.contains("}");
                auto state = 0;

                if (block.blockNumber() > 0) {
                    auto prevLevel = block.previous().userState();
                    state = prevLevel;
                    state += prevLevel % 2;
                }

                state = state + open;
                state = state - 2*close;

                QTextCursor cursor = QTextCursor(block);
                cursor.select(QTextCursor::LineUnderCursor);

                for (auto i = 0; i < state/2; ++i) {
                    cursor.insertText("\t");
                }

                cursor.insertText(line);
                block.setUserState(state);
                block = block.next();
            } while (block.isValid());
        }

        void Editor::run() {
            Code::Compiler::instance->setSource(this->getText());
        }

        void Editor::saveFile() {
            if (this->m_filePath.length() > 0 && IO::FileExists(this->m_filePath)) {
                IO::Write::TextToFile(this->getText(), this->m_filePath);
                this->setModified(false);
            } else {
                this->m_filePath = IO::FromDialog::SelectSaveFileUrl("*.qml");
                emit this->filePathChanged();

                if (IO::FileExists(this->m_filePath)) {
                    IO::Write::TextToFile(this->getText(), this->m_filePath);
                    this->setModified(false);
                }
            }
        }

        void Editor::openFile() {
            auto newFilePath = IO::FromDialog::SelectOpenFileUrl("*.qml");

            if (IO::FileExists(newFilePath)) {
                this->m_filePath = newFilePath;
                emit this->filePathChanged();

                this->setText(IO::Read::TextFromUrl(this->m_filePath));
                this->setModified(false);
                this->format();

                this->run();
            }
        }

        void Editor::newFile() {
            this->m_filePath = "";
            emit this->filePathChanged();

            this->setText("");
            this->setModified(false);
        }

        Editor::~Editor() {
            delete this->m_highlighter;
        }
    }
}