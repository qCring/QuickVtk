#pragma once

#include "quickCodeSelection.hpp"

#include <QTextCursor>
#include <QString>
#include <QList>

namespace quick {

    namespace Code {

        class Action {
        private:
            static QList<Action*> pool;
            Action();
            ~Action();
        public:
            enum class Type {
                Addition,
                Deletion
            } type;

            QString text;
            QString typeStr;
            int start = 0;
            int end = 0;
            int line = 0;
            int lines = 0;
            Action* next = nullptr;
            Action* prev = nullptr;

            static auto Addition(const Selection::Data&, QString = nullptr) -> Action*;
            static auto Deletion(const Selection::Data&, QString = nullptr) -> Action*;

            auto toString() -> std::string;
            auto getLast() -> Action*;
            auto setNext(Action* action) -> Action*;
        };
    }
}
