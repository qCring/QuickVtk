#include "quickSymbol.hpp"
#include "quickGroup.hpp"

namespace quick {

    Qml::Register::Type<Symbol> Symbol::Register;

    auto Symbol::CreateClassSymbol(QMetaObject metaObject) -> Symbol* {
        auto symbol = new Symbol();

        auto objName = QString(metaObject.className());
        symbol->m_color = "#319CD3";
        symbol->m_type = "class";
        symbol->m_prefix = objName.section("::", 1, 1);
        symbol->m_name = objName.section("::", 2, 2);

        QChar character = symbol->m_prefix.at(0);
        symbol->m_prefix = symbol->m_prefix.remove(0,1);
        symbol->m_prefix.push_front(character.toLower());

        return symbol;
    }

    auto Symbol::CreateAbstractClassSymbol(QMetaObject metaObject) -> Symbol* {
        auto symbol = new Symbol();

        auto objName = QString(metaObject.className());
        symbol->m_color = "#3B424C";
        symbol->m_type = "abstract";
        symbol->m_prefix = objName.section("::", 1, 1);
        symbol->m_name = objName.section("::", 2, 2);

        QChar character = symbol->m_prefix.at(0);
        symbol->m_prefix = symbol->m_prefix.remove(0,1);
        symbol->m_prefix.push_front(character.toLower());

        return symbol;
    }

    auto Symbol::matches(const QString& filter) -> bool {
        return this->m_name.contains(filter, Qt::CaseInsensitive);
    }

    auto Symbol::getName() -> QString {
        return this->m_name;
    }

    auto Symbol::getPrefix() -> QString {
        return this->m_prefix;
    }

    auto Symbol::getType() -> QString {
        return this->m_type;
    }

    auto Symbol::getColor() -> QColor {
        return this->m_color;
    }

    auto Symbol::add(Group* group) -> void {
        auto index = this->m_groups.count();

        beginInsertRows(QModelIndex(), index, index);
        this->m_groups.append(group);
        endInsertRows();
    }

    auto Symbol::clear() -> void {
        beginResetModel();
        this->m_groups.clear();
        endResetModel();
    }

    auto Symbol::roleNames() const -> QHash<int, QByteArray> {
        QHash<int, QByteArray> roles;
        roles[GroupRole] = "group";

        return roles;
    }

    auto Symbol::data(const QModelIndex& index, int role) const -> QVariant {
        QVariant var;

        if (index.isValid()) {
            if (role == GroupRole) {
                var.setValue(this->m_groups.at(index.row()));
            }
        }

        return var;
    }

    auto Symbol::rowCount(const QModelIndex&) const -> int {
        return this->m_groups.size();
    }
}
