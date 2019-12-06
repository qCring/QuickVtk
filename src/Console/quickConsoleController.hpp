#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick {

    namespace Console {

        class Item;
    
        class Controller : public QObject {
            Q_OBJECT
            Q_PROPERTY(QQmlListProperty<quick::Console::Item> items READ getItemList NOTIFY itemsChanged);
        private:
            static Qml::Register::Controller<Controller> Register;
            static Controller* instance;
            QList<Item*> m_items;
        private:
            Controller();
        public:
            static auto Create() -> void;
            static auto GetInstance() -> Controller*;
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
        };
    }
}
