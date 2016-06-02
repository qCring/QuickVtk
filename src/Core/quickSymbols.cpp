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

    auto Symbols::setFilter(const QString& filter) -> void {
        this->m_filter = filter;
        emit this->filterChanged();

        this->beginResetModel();
        this->m_symbols.clear();

        for (auto symbol : this->m_allSymbols) {
            if (symbol->matches(filter)) {
                this->m_symbols.append(symbol);
            }
        }

        this->endResetModel();
    }

    auto Symbols::getFilter() -> QString {
        return this->m_filter;
    }

    auto Symbols::Add(Symbol* symbol) -> void {
        if (!symbol) {
            return;
        }
        
        auto instance = GetInstance();

        instance->m_symbols.append(symbol);
        instance->m_allSymbols.append(symbol);
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
