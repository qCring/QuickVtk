#include "quickCodeAction.hpp"

#include <iostream>

namespace quick {

    namespace Code {

        QList<Action*> Action::pool = QList<Action*>();

        Action::Action() {

        }

        Action::~Action() {
            
        }

        auto Action::Addition(const Selection::Data& selection, QString text) -> Action* {
            auto action = new Action();

            if (text == nullptr) {
                action->text = selection.text;
            } else {
                action->text = text;
            }

            action->type = Type::Addition;
            action->start = selection.start;
            action->end = selection.end;
            action->line = selection.line;
            action->lines = selection.lines;

            action->typeStr = "add";

            if (selection.start == selection.end) {
                action->end += action->text.length();
            }

            if (action->text.length() < 1) {
                std::cout << "action.text is empty!\n";
            }

            std::cout << action->toString() << std::endl;

            return action;
        }

            auto Action::Deletion(const Selection::Data& selection, QString text) -> Action* {
            auto action = new Action();

            if (text == nullptr) {
                action->text = selection.text;
            } else {
                action->text = text;
            }

            action->type = Type::Deletion;
            action->start = selection.start;
            action->end = selection.end;
            action->line = selection.line;
            action->lines = selection.lines;

            if (selection.start == selection.end) {
                action->end += action->text.length();
            }

            if (action->text.length() < 1) {
                   std::cout << "action.text is empty!\n";
            }

            action->typeStr = "del";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::toString() -> std::string {

            QString s;
            s += "action: ";
            s += " type: " + typeStr;
            s += " text: " + text;
            s += " start: ";
            s += QString::number(start);
            s += " end: ";
            s += QString::number(end);

            return s.toStdString();
        }

        auto Action::getLast() -> Action* {

            auto current = this;

            while (current->next) {
                current = current->next;
            }

            return current;
        }

        auto Action::setNext(Action* action) -> Action* {
            this->next = action;
            action->prev = this;
            return this;
        }
    }
}
