#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Console {

        class Item;
    
        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Console::Item> items READ getItemList NOTIFY itemsChanged);
            Q_PROPERTY(bool collapsed READ getCollapsed WRITE setCollapsed NOTIFY collapsedChanged);
        private:
            static Qml::Register::Controller<Controller> Register;
            bool m_collapsed;
            QList<Item*> m_items;
        private:
            Controller();
        public:
            static Controller* instance;
            static auto Create() -> void;
            auto setCollapsed(bool) -> void;
            auto getCollapsed() -> bool;
            auto toggle() -> void;
            auto addInfoMsg(const QString&) -> void;
            auto addDebugMsg(const QString&) -> void;
            auto addWarningMsg(const QString&) -> void;
            auto addErrorMsg(const QString&) -> void;
            auto getItemList() -> QQmlListProperty<Item>;
            static auto itemCount(QQmlListProperty<Item>*) -> int;
            static auto itemAt(QQmlListProperty<Item>*, int) -> Item*;
        public slots:
            void clear();
        signals:
            void itemsChanged();
            void collapsedChanged();
        };
    }
}
