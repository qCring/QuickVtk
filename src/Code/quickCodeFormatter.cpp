#include "quickCodeFormatter.hpp"

#include "quickCodeEditor.hpp"

#include <QApplication>
#include <QTextCursor>
#include <QClipboard>
#include <QTextBlock>

#include <iostream>

namespace quick {

    namespace Code {

        auto Formatter::setTextDocument(QTextDocument* document) -> void {
            this->m_document = document;
        }

        auto Formatter::invalidateText() -> void {
            Editor::instance->setModified(true);
        }

        auto Formatter::handleRedo() -> bool {
            this->m_document->redo();
            this->invalidateText();
            return true;
        }

        auto Formatter::handleUndo() -> bool {
            this->m_document->undo();
            this->invalidateText();
            return true;
        }

        auto Formatter::handleShowSearch() -> bool {
            Editor::instance->showSearch();
            return true;
        }

        auto Formatter::handlePaste() -> bool {
            auto text = QApplication::clipboard()->text();

            if (!text.isEmpty())
            {
                auto cursor = Editor::instance->getCurrentCursor();
                cursor.beginEditBlock();
                cursor.insertText(text);
                cursor.endEditBlock();

                this->invalidateText();
            }
            return true;
        }

        auto Formatter::format() -> void {
            auto block = this->m_document->firstBlock();
            auto lines = Editor::instance->getLines();
            lines.clear();

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

                /*
                 QTextCursor cursor = QTextCursor(block);
                 cursor.select(QTextCursor::LineUnderCursor);

                 for (auto i = 0; i < state/2; ++i) {
                 cursor.insertText("\t");
                 }*/

                lines.append(state);
                // cursor.insertText(line);
                block.setUserState(state);
                block = block.next();
            } while (block.isValid());

            Editor::instance->setLines(lines);
        }

        auto Formatter::handleEnter() -> bool {
            auto cursor = Editor::instance->getCurrentCursor();
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
                auto blockNumber = block.blockNumber();

                auto lines = Editor::instance->getLines();
                //std::cout << "lines: " << lines.count() << std::endl;
                //std::cout << "block: " << blockNumber << std::endl;

                if (blockNumber >= lines.count()) {
                    lines.append(newLevel);
                } else {
                    lines.insert(blockNumber, newLevel);
                }

                for (auto i = 0; i < newLevel / 2; i++) {
                    cursor.insertText("\t");
                }

                Editor::instance->setLines(lines);
            }

            else {
                cursor.insertBlock();
                auto level = block.userState();

                for (auto i = 0; i < level / 2; i++) {
                    cursor.insertText("\t");
                }
            }

            cursor.endEditBlock();
            this->invalidateText();
                
            return true;
        }

        auto Formatter::handleCloseBraces() -> bool {
            auto cursor = Editor::instance->getCurrentCursor();
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

            this->invalidateText();

            return true;
        }

        auto Formatter::onKeyPressed(int key, int modifiers, const QString& string) -> bool {
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

            if (string == "}") {
                return handleCloseBraces();
            }

            if (QRegularExpression("(\\w+)|(\\W+)").match(string).hasMatch()) {
                this->invalidateText();
            }

            return false;
        }
    }
}
