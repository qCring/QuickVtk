#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {

    namespace TypeInfo {

        class Item;

        class List : public QAbstractListModel {
            Q_OBJECT
            Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged);
            Q_PROPERTY(QString filter READ getFilter WRITE setFilter NOTIFY filterChanged);
        public:
            enum Roles {
                ItemRole = Qt::UserRole + 1
            };
        private:
            Item* m_selectedItem = nullptr;
            bool m_visible = false;
            QString m_filter;
            QList<Item*> m_items;
            QList<Item*> m_allItems;
        private:
            static auto Add(Item*) -> void;
        public:
            static Qml::Register::Type<List> Register;
            static auto GetInstance() -> List*;
            static auto AddEnum(QMetaEnum) -> void;
            static auto AddClass(QMetaObject) -> void;
            static auto AddAbstract(QMetaObject) -> void;
            static auto GetEnums() -> QStringList&;
            auto selectItem(Item*) -> void;
            auto setVisible(bool) -> void;
            auto isVisible() -> bool;
            auto setFilter(const QString&) -> void;
            auto getFilter() -> QString;
            auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
            auto data(const QModelIndex&, int) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            void clear();
        signals:
            void visibleChanged();
            void filterChanged();
        };
    }
}