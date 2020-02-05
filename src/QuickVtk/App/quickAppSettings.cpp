#include "quickAppSettings.hpp"

namespace quick::App {

    Settings* Settings::instance = nullptr;

    Qml::Register::Controller<Settings> Settings::Register;

    auto Settings::Create() -> void {
        if (instance) {
            throw std::runtime_error("instance already existing");
        }
        
        instance = new Settings();
    }

    auto Settings::LoadRecentFiles() -> QStringList {
        QSettings settings;
        return settings.value(Key::RecentFiles).toStringList();
    }

    auto Settings::SaveRecentFiles(const QStringList& list) -> void{
        QSettings settings;
        settings.setValue(Key::RecentFiles, list);
    }

    auto Settings::ClearRecentFiles() -> void {
        QSettings settings;
        settings.remove(Key::RecentFiles);
    }

    auto Settings::GetRecentFilesCount() -> int {
        return instance->m_recentFilesCount;
    }
}
