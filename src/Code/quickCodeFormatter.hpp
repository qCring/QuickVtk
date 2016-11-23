#pragma once

#include <QStack>
#include <QTextDocument>

namespace quick {

    namespace Code {

        class Action;
        
        class Formatter {
        private:
            QTextDocument* m_document = nullptr;
        private:
            friend class Editor;
            QStack<Action*> undoStack;
            QStack<Action*> redoStack;
            QList<int> m_lines;
        private:
            auto invalidateText() -> void;
            auto handleUndo() -> bool;
            auto handleRedo() -> bool;
            auto handlePaste() -> bool;
            auto handleEnter() -> bool;
            auto handleShowSearch() -> bool;
            auto handleCloseBraces() -> bool;
            auto handleEscape() -> bool;
            auto handleBackspace() -> bool;
            auto handleBacktab() -> bool;
            auto insertText(const QString&) -> void;
        public:
            Formatter();
            auto format() -> void;
            auto reset() -> void;
            auto setTextDocument(QTextDocument*) -> void;
            auto onKeyPressed(int, int, const QString&) -> bool;
        };
    }
}
