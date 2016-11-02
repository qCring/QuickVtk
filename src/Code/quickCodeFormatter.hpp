#pragma once

#include <QTextDocument>

namespace quick {

    namespace Code {

        class Formatter {
        private:
            QTextDocument* m_document = nullptr;
        private:
            auto invalidateText() -> void;
            auto handleUndo() -> bool;
            auto handleRedo() -> bool;
            auto handlePaste() -> bool;
            auto handleEnter() -> bool;
            auto handleShowSearch() -> bool;
            auto handleCloseBraces() -> bool;
        public:
            auto format() -> void;
            auto setTextDocument(QTextDocument*) -> void;
            auto onKeyPressed(int, int, const QString&) -> bool;
        };
    }
}
