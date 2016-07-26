#pragma once

#include <QString>
#include <QQuickView>

namespace quick {

    namespace App {

        class Window {
        private:
            QQuickView* m_view = nullptr;
            QString resourceDir;
        private:
            auto init() -> void;
            auto AddFontDir(const QString&) -> void;
        public:
            static Window* instance;
            auto getResourceDir() -> QString;
            Window();
            auto start(int, char**) -> int;
        };
    }
}