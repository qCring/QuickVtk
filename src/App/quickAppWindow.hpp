#pragma once

#include <QString>
#include <QQuickView>

namespace quick {
    namespace App {
        class Window {
        private:
            QQuickView* m_view = nullptr;
            QString resourceDir;
            auto AddFontDir(const QString&) -> void;
        public:
            static Window* instance;
            Window();
            auto start(int, char**) -> int;
        };
    }
}