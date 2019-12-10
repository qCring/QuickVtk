#include "quickAppSettings.hpp"
#include "quickAppMenu.hpp"

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
    
        auto Settings::Init() -> void {
            QSettings settings;
            auto files = settings.value("menu/recent").toList();
            
            for (const auto& entry : files) {
                instance->m_recentFiles << entry.toString();
            }
        }
    
        auto Settings::AddRecentFile(const QString& filePath) -> void {
            instance->m_recentFiles.append(filePath);
            QSettings settings;
            settings.setValue("menu/recent", instance->m_recentFiles);
        }
    
        auto Settings::RemoveRecentFile(const QString& filePath) -> void {
            instance->m_recentFiles.removeOne(filePath);
            QSettings settings;
            settings.setValue("menu/recent", instance->m_recentFiles);
        }
    
        auto Settings::GetRecentFiles() -> QStringList {
            return instance->m_recentFiles;
        }
    
        auto Settings::setVisible(bool visible) -> void {
            if (this->m_visible != visible) {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }
    
        auto Settings::getVisible() -> bool {
            return this->m_visible;
        }
    
        void Settings::reset() {
            QSettings settings;
            settings.remove("menu/recent");
            instance->m_recentFiles.clear();
            Menu::instance->clearRecentFiles();
        }
    }
}
