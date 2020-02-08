#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::Console {

    class Item;

    class Controller : public QObject {
        Q_OBJECT
        Q_PROPERTY(QQmlListProperty<quick::Console::Item> items READ getItemList NOTIFY itemsChanged);
        Q_PROPERTY(bool collapsed READ getCollapsed WRITE setCollapsed NOTIFY collapsedChanged);
        Q_PROPERTY(int errorCount READ getErrorCount NOTIFY errorCountChanged);
        Q_PROPERTY(int warningCount READ getWarningCount NOTIFY warningCountChanged);
    private:
        static Qml::Register::Controller<Controller> Register;
        bool m_collapsed = true;
        int m_errorCount = 0;
        int m_warningCount = 0;
        QList<Item*> m_items;
    private:
        Controller();
    public:
        static Controller* instance;
        static auto Create() -> void;
        auto setCollapsed(bool) -> void;
        auto getCollapsed() -> bool;
        auto getErrorCount() -> int;
        auto getWarningCount() -> int;
        auto addInfoMsg(const QString&) -> void;
        auto addDebugMsg(const QString&) -> void;
        auto addWarningMsg(const QString&) -> void;
        auto addErrorMsg(const QString&) -> void;
        auto getItemList() -> QQmlListProperty<Item>;
        static auto itemCount(QQmlListProperty<Item>*) -> int;
        static auto itemAt(QQmlListProperty<Item>*, int) -> Item*;
    public slots:
        void clear();
        void toggle();
    signals:
        void errorCountChanged();
        void warningCountChanged();
        void itemsChanged();
        void collapsedChanged();
    };
}
