#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class Settings : public QObject {
            Q_OBJECT
        private:
            static Qml::Register::Controller<Settings> Register;
            Settings();
            QStringList m_recentFiles;
        public:
            static Settings* instance;
            static auto Create() -> void;
            static auto Init() -> void;
            static auto ClearRecentFiles() -> void;
            static auto AddRecentFile(const QString&) -> void;
            static auto GetRecentFiles() -> QStringList;
        };
    }
}
