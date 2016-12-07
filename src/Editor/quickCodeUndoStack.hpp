#pragma once

#include <QList>

namespace quick {

    namespace Code {

        class Action;

        class UndoStack {
        private:
            QList<Action*> m_undoStack;
            QList<Action*> m_redoStack;
            int m_stackSize = 10;
        public:
            bool chainActions = true;
        public:
            auto PushUndo(Action*) -> void;
            auto PopUndo() -> Action*;
            auto PushRedo(Action*) -> void;
            auto PopRedo() -> Action*;
            auto setStackSize(int) -> void;
            auto getStackSize() -> int;
            ~UndoStack();
        };
    }
}
