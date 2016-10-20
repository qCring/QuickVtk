#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class Settings : public QObject {
            Q_OBJECT
            Q_PROPERTY(int cursorFlashTime READ getCursorFlashTime CONSTANT);
        private:
            static Qml::Register::Controller<Settings> Register;
            Settings();
        public:
            static Settings* instance;
            static auto Create() -> void;
            auto getCursorFlashTime() -> int;
        };
    }
}
