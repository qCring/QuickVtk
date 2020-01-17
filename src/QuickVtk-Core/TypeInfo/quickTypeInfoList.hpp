#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {
    namespace TypeInfo {

        class Symbol;

        class List : public QAbstractListModel {
            Q_OBJECT
            Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged);
            Q_PROPERTY(QString filter READ getFilter WRITE setFilter NOTIFY filterChanged);
            Q_PROPERTY(int totalCount READ getTotalCount CONSTANT);
            Q_PROPERTY(int count READ getCount NOTIFY countChanged);
        public:
            enum Roles {
                SymbolRole = Qt::UserRole + 1
            };
        private:
            friend class Symbol;
            bool m_visible = false;
            QString m_filter;
            QList<Symbol*> m_symbols;
            QList<Symbol*> m_allSymbols;
        private:
            static auto Add(Symbol*) -> void;
            static QMap<QString, class Enum*> EnumLookup;
        public:
            static Qml::Register::Type<List> Register;
            static auto GetInstance() -> List*;
            static auto GetEnumLookup() -> QMap<QString, class Enum*>;
            auto init() -> void;
            auto setVisible(bool) -> void;
            auto isVisible() -> bool;
            auto setFilter(const QString&) -> void;
            auto getFilter() -> QString;
            auto getCount() -> int;
            auto getTotalCount() -> int;
            auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
            auto data(const QModelIndex&, int) const -> QVariant;
            auto roleNames() const -> QHash<int, QByteArray>;
            auto getAllSymbols() -> QList<Symbol*>;
        signals:
            void visibleChanged();
            void filterChanged();
            void countChanged();
        };
    }
}
