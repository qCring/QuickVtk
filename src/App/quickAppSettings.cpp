#include "quickAppSettings.hpp"

#include <QApplication>

namespace quick {

    namespace App {

        Settings* Settings::instance = nullptr;

        Qml::Register::Controller<Settings> Settings::Register;

        Settings::Settings() {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Settings::Create() -> void {
            instance = new Settings();
        }

        auto Settings::getCursorFlashTime() -> int {
            return QApplication::cursorFlashTime() / 2;
        }
    }
}
