#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class Settings : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
        private:
            static Qml::Register::Controller<Settings> Register;
            bool m_visible;
            Settings();
            QStringList m_recentFiles;
        public:
            static Settings* instance;
            static auto Create() -> void;
            static auto Init() -> void;
            static auto AddRecentFile(const QString&) -> void;
            static auto GetRecentFiles() -> QStringList;
        public:
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
        public slots:
            void reset();
        signals:
            void visibleChanged();
        };
    }
}
