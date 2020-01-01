#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace App {

        class Details : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool collapsed READ getCollapsed WRITE setCollapsed NOTIFY collapsedChanged);
            Q_PROPERTY(bool properties READ getProperties NOTIFY propertiesChanged);
            Q_PROPERTY(bool settings READ getSettings NOTIFY settingsChanged);
            Q_PROPERTY(bool types READ getTypes NOTIFY typesChanged);
            Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged);
        private:
            bool m_collapsed = true;
            bool m_properties = true;
            bool m_settings = false;
            bool m_types = false;
            QString m_title;
            static Qml::Register::Controller<Details> Register;
            Details() = default;
        private:
            auto setTitle(const QString&) -> void;
        public:
            static Details* instance;
            static auto Create() -> void;
            auto setCollapsed(bool) -> void;
            auto getCollapsed() -> bool;
            auto getProperties() -> bool;
            auto getSettings() -> bool;
            auto getTypes() -> bool;
            auto getTitle() -> QString;
        public slots:
            void toggle();
            void showProperties();
            void showSettings();
            void showTypes();
        signals:
            void titleChanged();
            void collapsedChanged();
            void propertiesChanged();
            void settingsChanged();
            void typesChanged();
        };
    }
}
