#include "quickCodeUndoStack.hpp"

#include <iostream>

namespace quick {

    namespace Code {

        auto Change::Empty() -> Change {
            auto change = Change();

            change.empty = true;

            return change;
        }
        
        Change::Change(Type type, int start, int end, const QString& selection, const QString& text) {
            this->type = type;
            this->empty = false;
            this->start = start;
            this->end = end;
            this->selection = selection;
            this->text = text;
        }

        auto Change::Insert(const Selection::Data& selection, const QString& text) -> Change {
            auto change = Change();

            change.type = Type::InsertText;
            change.empty = false;
            change.start = selection.start;
            change.end = selection.end;
            change.selection = selection.text;
            change.text = text;

            return change;
        }

        auto Change::Delete(const Selection::Data& selection) -> Change {
            auto change = Change();

            change.type = Type::DeleteText;
            change.empty = false;
            change.start = selection.start;
            change.end = selection.end;
            change.selection = selection.text;

            return change;
        }

        auto Change::toString() -> std::string {
            return QString(" s: " + QString::number(start) + " e: " + QString::number(end) + " sel: " + selection + " text: " + text).toStdString();
        }

        auto UndoStack::pushUndo(Change change) -> void {
            std::cout << "push undo: " << change.toString() << std::endl;

            if (this->m_undoStack.count() >= m_stackSize) {
                this->m_undoStack.removeAt(0);
            }

            this->m_undoStack.append(change);
        }

        auto UndoStack::popUndo() -> Change {
            std::cout << "pop undo\n";

            if (this->m_undoStack.count() > 0) {
                return this->m_undoStack.takeLast();
            }

            return Change::Empty();
        }

        auto UndoStack::pushRedo(Change change) -> void {
            if (this->m_redoStack.count() >= m_stackSize) {
                this->m_redoStack.removeAt(0);
            }

            this->m_redoStack.append(change);
        }

        auto UndoStack::popRedo() -> Change {
            if (this->m_redoStack.count() > 0) {
                return this->m_redoStack.takeLast();
            }

            return Change::Empty();
        }

        auto UndoStack::setStackSize(int stackSize) -> void {
            this->m_stackSize = stackSize;
        }

        auto UndoStack::getStackSize() -> int {
            return this->m_stackSize;
        }
    }
}
