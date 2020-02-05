#pragma once

#include "quickQmlRegister.hpp"

#include <QObject>

namespace quick::Menu {
    
    enum class Action {
        None,
        File_Open,
        File_Open_Recent,
        File_Clear_History,
        File_Close,
        File_Quit,
        View_Console,
        View_Inspector,
        View_Previous_Tab,
        View_Next_Tab
    };

    enum class Separator {
        On,
        Off
    };

    class Item : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString label READ getLabel WRITE setLabel NOTIFY labelChanged);
        Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
        Q_PROPERTY(QQmlListProperty<quick::Menu::Item> items READ getItemList NOTIFY itemsChanged);
        Q_PROPERTY(bool separator READ getSeparator CONSTANT);
        Q_PROPERTY(bool enabled READ getEnabled WRITE setEnabled NOTIFY enabledChanged);
    private:
        QString m_label;
        QString m_icon;
        QString m_data;
        QList<Item*> m_items;
        bool m_separator = false;
        bool m_enabled = true;
        static Qml::Register::Type<Item> Register;
    public:
        static auto itemsCount(QQmlListProperty<Item>*) -> int;
        static auto itemsAt(QQmlListProperty<Item>*, int) -> Item*;
        const Action action;
    private:
        Item(const QString&, const QString&, Action action, Separator separator);
    public:
        class Create {
        public:
            static auto SimpleItem(const QString& label, Action action = Action::None, Separator separator = Separator::Off) -> Item*;
            static auto IconItem(const QString& label, const QString& icon, Action action = Action::None, Separator separator = Separator::Off) -> Item*;
        };
    public:
        auto setLabel(const QString&) -> void;
        auto getLabel() -> QString;
        auto setData(const QString&) -> void;
        auto getData() -> QString;
        auto setIcon(const QString&) -> void;
        auto getIcon() -> QString;
        auto setEnabled(bool) -> void;
        auto getEnabled() -> bool;
        auto getSeparator() -> bool;
        auto getItemList() -> QQmlListProperty<Item>;
        auto getItems() -> QList<Item*>;
        auto add(Item*) -> void;
        auto removeItems() -> void;
        auto removeItem(const QString&) -> void;
        auto isEmpty() -> bool;
    signals:
        void labelChanged();
        void iconChanged();
        void itemsChanged();
        void enabledChanged();
    };
}
