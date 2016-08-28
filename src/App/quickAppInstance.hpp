#pragma once

#include <QString>
#include <QQuickView>

namespace quick {

    namespace App {

        class Instance {
        private:
            QQuickView* m_view = nullptr;
            QString resourceDir;
        private:
            static Instance* instance;
            Instance();
            auto init() -> void;
            auto AddFontDir(const QString&) -> void;
        public:
            static auto GetResourceDir() -> QString;
            static auto Execute(int, char**) -> int;
        };
    }
}