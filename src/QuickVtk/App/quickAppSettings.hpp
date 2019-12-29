#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace App {

        class Settings : public QObject {
            Q_OBJECT
        private:
            class Key {
            public:
                static constexpr auto RecentFiles = "history/files";
            };
        private:
            static Qml::Register::Controller<Settings> Register;
            Settings() = default;
            int m_recentFilesCount = 5;
        public:
            static Settings* instance;
            static auto Create() -> void;
            static auto LoadRecentFiles() -> QStringList;
            static auto SaveRecentFiles(const QStringList&) -> void;
            static auto ClearRecentFiles() -> void;
            static auto GetRecentFilesCount() -> int;
        };
    }
}
