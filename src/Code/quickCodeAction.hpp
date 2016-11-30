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
                InsertChar,
                InsertNewline,
                DeleteSelection,
                DeletePreviousChar
            } type;

            QChar character;
            QString text;
            QString typeStr;
            int start = 0;
            int end = 0;
            int line = 0;
            int lines = 0;
            Action* next = nullptr;
            Action* prev = nullptr;

            static auto InsertChar(const Selection::Data&, const QChar&) -> Action*;
            static auto InsertNewline(const Selection::Data&) -> Action*;
            static auto DeleteSelection(const Selection::Data&) -> Action*;
            static auto DeletePreviousChar(const Selection::Data&, const QChar&) -> Action*;

            auto toString() -> std::string;
            auto getLast() -> Action*;
            auto setNext(Action* action) -> Action*;
        };
    }
}
