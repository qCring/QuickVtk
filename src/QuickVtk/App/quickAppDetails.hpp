#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {
    namespace App {

        class Details : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool collapsed READ getCollapsed WRITE setCollapsed NOTIFY collapsedChanged);
            Q_PROPERTY(bool info READ getInfo NOTIFY infoChanged);
            Q_PROPERTY(bool types READ getTypes NOTIFY typesChanged);
            Q_PROPERTY(bool notifications READ getNotifications NOTIFY notificationsChanged);
            Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged);
        private:
            bool m_collapsed = true;
            bool m_info = true;
            bool m_types = false;
            bool m_notifications = false;
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
            auto getInfo() -> bool;
            auto getTypes() -> bool;
            auto getNotifications() -> bool;
            auto getTitle() -> QString;
        public slots:
            void toggle();
            void showInfo();
            void showTypes();
            void showNotifications();
        signals:
            void titleChanged();
            void collapsedChanged();
            void infoChanged();
            void typesChanged();
            void notificationsChanged();
        };
    }
}
