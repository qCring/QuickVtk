#pragma once

#include "quickCodeSelection.hpp"

#include <QTextCursor>
#include <QString>

namespace quick {

    namespace Code {

        class Action {
        private:
        private:
            auto setPrev(Action* action) -> void;
        public:
            enum class Type {
                InsertChar,
                InsertNewline,
                DeleteNextChar,
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

            static auto InsertChar(const Selection::Data&, const QChar&, Action*) -> Action*;
            static auto InsertNewline(const Selection::Data&, Action*) -> Action*;
            static auto DeleteSelection(const Selection::Data&) -> Action*;
            static auto DeleteNextChar(int, const QChar&, Action*) -> Action*;
            static auto DeletePreviousChar(const Selection::Data&, const QChar&, Action*) -> Action*;

            auto toString() -> std::string;
            auto getLast() -> Action*;
        };
    }
}
