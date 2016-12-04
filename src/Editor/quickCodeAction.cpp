#include "quickCodeAction.hpp"

#include <iostream>

namespace quick {

    namespace Code {

        auto Action::InsertChar(const Selection::Data& selection, const QChar& c, Action* prev) -> Action* {
            auto action = new Action();

            action->setPrev(prev);

            action->type = Type::InsertChar;
            action->start = selection.start;
            action->end = selection.start;
            action->character = c;

            action->typeStr = "insert char";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::InsertText(const Selection::Data& selection, const QString& text, Action* prev) -> Action* {
            auto action = new Action();

            action->setPrev(prev);

            action->type = Type::InsertText;
            action->start = selection.start;
            action->end = selection.start + text.length();
            action->text = text;

            action->typeStr = "insert text";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::InsertNewline(const Selection::Data& selection, Action* prev) -> Action* {
            auto action = new Action();

            action->setPrev(prev);

            action->type = Type::InsertNewline;
            action->start = selection.start;
            action->end = selection.start;

            action->typeStr = "insert nl";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::DeleteNextChar(int start, const QChar& c, Action* prev) -> Action* {
            auto action = new Action();

            action->setPrev(prev);

            action->type = Type::DeleteNextChar;
            action->start = start;
            action->end = start;
            action->character = c;

            std::cout << action->toString() << std::endl;
            std::cout << "char: " << c.toLatin1() << std::endl;

            return action;
        }

        auto Action::DeletePreviousChar(const Selection::Data& selection, const QChar& c, Action* prev) -> Action* {
            auto action = new Action();

            action->setPrev(prev);

            action->type = Type::DeletePreviousChar;
            action->start = selection.start;
            action->end = selection.start;
            action->character = c;

            action->typeStr = "del prev char";

            std::cout << action->toString() << std::endl;
            std::cout << "char: " << c.toLatin1() << std::endl;
            
            return action;
        }

        auto Action::DeleteSelection(const Selection::Data& selection) -> Action* {
            auto action = new Action();

            action->type = Type::DeleteSelection;
            action->start = selection.start;
            action->end = selection.end;
            action->line = selection.line;
            action->lines = selection.lines;
            action->text = selection.text;

            action->typeStr = "del selection";

            std::cout << action->toString() << std::endl;
            
            return action;
        }

        auto Action::toString() -> std::string {

            QString s;
            s += "action: ";
            s += " type: " + typeStr;
            s += " start: ";
            s += QString::number(start);
            s += " end: ";
            s += QString::number(end);
            s += " text: " + text;

            return s.toStdString();
        }

        auto Action::getLast() -> Action* {

            auto current = this;

            while (current->next) {
                current = current->next;
            }

            return current;
        }

        auto Action::setPrev(Action* action) -> void {
            this->prev = action;

            if (action != nullptr) {
                action->next = this;
            }
        }
    }
}
