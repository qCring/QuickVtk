#pragma once

#include "quickCodeSelection.hpp"

#include <QList>

namespace quick {

    namespace Code {

        class Change {
        private:
            Change() = default;
        public:
            bool empty = true;
            int start = 0;
            int end = 0;
            QString text;
            QString selection;
        public:
            Change(int, int, const QString&, const QString&);
            static auto Empty() -> Change;
            static auto Insert(const Selection::Data&, const QString&) -> Change;
            auto toString() -> std::string;
        };

        class UndoStack {
        private:
            QList<Change> m_undoStack;
            QList<Change> m_redoStack;
            int m_stackSize = 10;
        public:
            auto pushUndo(Change) -> void;
            auto popUndo() -> Change;
            auto pushRedo(Change) -> void;
            auto popRedo() -> Change;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
        };
    }
}
