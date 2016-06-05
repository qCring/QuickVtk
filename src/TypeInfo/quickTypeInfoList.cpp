#include "quickTypeInfoList.hpp"
#include "quickTypeInfoSymbol.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<List> List::Register;

        auto List::GetInstance() -> List* {
            static List* instance = new List();
            return instance;
        }

        auto List::selectItem(Symbol* symbol) -> void {
            if (this->m_selectedSymbol) {
                this->m_selectedSymbol->setSelected(false);
            }

            if (symbol) {
                symbol->setSelected(true);
            }

            this->m_selectedSymbol = symbol;
        }   

        auto List::setVisible(bool visible) -> void {
            if (this->m_visible != visible) {
                this->m_visible = visible;
                emit this->visibleChanged();
            }
        }

        auto List::isVisible() -> bool {
            return this->m_visible;
        }

        auto List::setFilter(const QString& filter) -> void {
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

        auto List::getFilter() -> QString {
            return this->m_filter;
        }

        auto List::Add(Symbol* symbol) -> void {
            if (!symbol) {
                return;
            }

            auto instance = GetInstance();

            instance->m_symbols.append(symbol);
            instance->m_allSymbols.append(symbol);
        }

        auto List::roleNames() const -> QHash<int, QByteArray> {
            QHash<int, QByteArray> roles;
            roles[SymbolRole] = "symbol";

            return roles;
        }

        auto List::data(const QModelIndex& index, int role) const -> QVariant {
            QVariant var;
            
            if (index.isValid()) {
                if (role == SymbolRole) {
                    var.setValue(this->m_symbols.at(index.row()));
                }
            }
            
            return var;
        }
        
        auto List::rowCount(const QModelIndex&) const -> int {
            return this->m_symbols.size();
        }
    }
}