#pragma once

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
            int position;
            Action* next = nullptr;
            Action* prev = nullptr;

            static auto Addition(const QString& text, int position) -> Action*;
            static auto Deletion(const QString& text, int position) -> Action*;

            auto toString() -> std::string;
            auto getLast() -> Action*;
            auto setNext(Action* action) -> Action*;
        };
    }
}
