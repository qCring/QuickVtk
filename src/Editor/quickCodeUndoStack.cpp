#include "quickCodeUndoStack.hpp"

#include "quickCodeAction.hpp"

namespace quick {

    namespace Code {

        auto UndoStack::PushUndo(Action* action) -> void {
            if (this->m_undoStack.count() >= m_stackSize) {
                delete this->m_undoStack.takeFirst();
            }

            this->m_undoStack.append(action);
        }

        auto UndoStack::PopUndo() -> Action* {
            if (this->m_undoStack.count() > 0) {
                return this->m_undoStack.takeLast();
            }

            return nullptr;
        }

        auto UndoStack::PushRedo(Action* action) -> void {
            if (this->m_redoStack.count() >= m_stackSize) {
                delete this->m_redoStack.takeFirst();
            }

            this->m_redoStack.append(action);
        }

        auto UndoStack::PopRedo() -> Action* {
            if (this->m_redoStack.count() > 0) {
                return this->m_redoStack.takeLast();
            }

            return nullptr;
        }

        auto UndoStack::setStackSize(int stackSize) -> void {
            this->m_stackSize = stackSize;
        }

        auto UndoStack::getStackSize() -> int {
            return this->m_stackSize;
        }

        UndoStack::~UndoStack() {
            for (auto action : this->m_undoStack) {
                delete action;
            }

            for (auto action : this->m_redoStack) {
                delete action;
            }

            this->m_undoStack.clear();
            this->m_redoStack.clear();
        }
    }
}
