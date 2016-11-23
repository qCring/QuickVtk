#include "quickCodeAction.hpp"

#include <iostream>

namespace quick {

    namespace Code {

        QList<Action*> Action::pool = QList<Action*>();

        Action::Action() {

        }

        Action::~Action() {
            
        }

        auto Action::Addition(const QString& text, int position) -> Action* {
            auto action = new Action();

            action->text = text;
            action->type = Type::Addition;
            action->position = position;

            action->typeStr = "add";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::Deletion(const QString& text, int position) -> Action* {
            auto action = new Action();

            action->text = text;
            action->type = Type::Deletion;
            action->position = position;

            action->typeStr = "del";

            std::cout << action->toString() << std::endl;

            return action;
        }

        auto Action::toString() -> std::string {

            QString s;
            s += "action: ";
            s += " type: " + typeStr;
            s += " text: " + text;
            s += " pos: ";
            s += QString::number(position);

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
