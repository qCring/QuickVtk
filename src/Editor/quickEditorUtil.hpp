#pragma once

#include <QTextDocument>
#include <QTextCursor>

namespace quick {

    namespace Editor {

        class Util {
        private:
            Util() = delete;
        public:
            static QTextDocument* document;
            static auto GetCursor (const int) -> QTextCursor;
            static auto GetLine (const int) -> QString;
            static auto GetChar(const int) -> QChar;
        };
    }
}
