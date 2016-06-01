#pragma once

#include "quickQmlRegister.hpp"

#include <QAbstractListModel>

namespace quick {

    class Symbol;

    class Symbols : public QAbstractListModel {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged);
    public:
        enum Roles {
            SymbolRole = Qt::UserRole + 1
        };
    private:
        bool m_visible = false;
        QList<Symbol*> m_symbols;
    public:
        static Qml::Register::Type<Symbols> Register;
        static auto GetInstance() -> Symbols*;
        static auto Add(Symbol*) -> void;
        auto setVisible(bool) -> void;
        auto isVisible() -> bool;
        auto rowCount(const QModelIndex& = QModelIndex()) const -> int;
        auto data(const QModelIndex&, int) const -> QVariant;
        auto roleNames() const -> QHash<int, QByteArray>;
        void clear();
    signals:
        void visibleChanged();
    };
}
