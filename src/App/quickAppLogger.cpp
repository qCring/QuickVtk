#include "quickAppLogger.hpp"

#include <iostream>

namespace quick {

    namespace App {

        Logger* Logger::instance = nullptr;
        Qml::Register::Controller<Logger> Logger::Register;

        Logger::Logger() {
        }

        auto Logger::Create() -> void {
            instance = new Logger();
        }

        auto Logger::GetInstance() -> Logger* {
            return instance;
        }

        void Logger::clear() {
            this->m_entries.clear();
            emit this->entriesChanged();
        }

        auto Logger::addEntry(const QString& entry) -> void {
            this->m_entries.append(entry);

            QMetaObject::invokeMethod(this, "entriesChanged", Qt::QueuedConnection);
        }

        auto Logger::getEntries() -> QStringList {
            return this->m_entries;
        }

        auto Logger::setVisible(bool visible) -> void {
            if (this->m_visible != visible) {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }

        auto Logger::getVisible() -> bool {
            return this->m_visible;
        }
    }
}
