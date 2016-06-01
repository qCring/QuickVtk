#include "quickSymbols.hpp"
#include "quickSymbol.hpp"

namespace quick {

    Qml::Register::Type<Symbols> Symbols::Register;

    auto Symbols::GetInstance() -> Symbols* {
        static Symbols* instance = new Symbols();
        return instance;
    }

    auto Symbols::setVisible(bool visible) -> void {
        if (this->m_visible != visible) {
            this->m_visible = visible;
            emit this->visibleChanged();
        }
    }

    auto Symbols::isVisible() -> bool {
        return this->m_visible;
    }

    auto Symbols::Add(Symbol* symbol) -> void {
        auto instance = GetInstance();
        auto index = instance->m_symbols.count();

        instance->beginInsertRows(QModelIndex(), index, index);
        instance->m_symbols.append(symbol);
        instance->endInsertRows();
    }

    auto Symbols::clear() -> void {
        beginResetModel();
        this->m_symbols.clear();
        endResetModel();
    }

    auto Symbols::roleNames() const -> QHash<int, QByteArray> {
        QHash<int, QByteArray> roles;
        roles[SymbolRole] = "symbol";

        return roles;
    }

    auto Symbols::data(const QModelIndex& index, int role) const -> QVariant {
        QVariant var;

        if (index.isValid()) {
            if (role == SymbolRole) {
                var.setValue(this->m_symbols.at(index.row()));
            }
        }

        return var;
    }

    auto Symbols::rowCount(const QModelIndex&) const -> int {
        return this->m_symbols.size();
    }
}
