#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace App {

        class Logger : public QObject {
            Q_OBJECT
            Q_PROPERTY(QStringList entries READ getEntries NOTIFY entriesChanged);
            Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged);
        private:
            static Qml::Register::Controller<Logger> Register;
            static Logger* instance;
            QStringList m_entries;
            bool m_visible = false;
        private:
            Logger();
        public:
            static auto Create() -> void;
            static auto GetInstance() -> Logger*;
            auto addEntry(const QString&) -> void;
            auto getEntries() -> QStringList;
            auto setVisible(bool) -> void;
            auto getVisible() -> bool;
        signals:
            void entriesChanged();
            void visibleChanged();
        };
    }
}
