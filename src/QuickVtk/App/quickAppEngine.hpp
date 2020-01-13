#pragma once

#include <QString>
#include <QThreadStorage>

namespace quick {
    namespace App {

        class Engine {
        private:
            QString resourceDir;
        private:
            Engine() = default;
            static Engine* instance;
            QThreadStorage<bool> m_messageHandled;
            auto init() -> void;
            auto AddFontDir(const QString&) -> void;
            static auto HandleMessage(QtMsgType, const QMessageLogContext&, const QString&) -> void;
        public:
            static auto GetResourceDir() -> QString;
            static auto Execute(int, char**) -> int;
        };
    }
}
