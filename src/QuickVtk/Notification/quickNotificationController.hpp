#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Notification {

        class Item;
    
        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Notification::Item> items READ getItemList NOTIFY itemsChanged);
        private:
            static Qml::Register::Controller<Controller> Register;
            QList<Item*> m_items;
        private:
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> void;
            auto getItemList() -> QQmlListProperty<Item>;
            auto addInfo(const QString&, const QString&) -> void;
            auto addWarning(const QString&, const QString&) -> void;
            auto addError(const QString&, const QString&) -> void;
            static auto itemCount(QQmlListProperty<Item>*) -> int;
            static auto itemAt(QQmlListProperty<Item>*, int) -> Item*;
        public slots:
            void clear();
        signals:
            void itemsChanged();
        };
    }
}
