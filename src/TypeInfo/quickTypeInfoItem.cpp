#include "quickTypeInfoItem.hpp"
#include "quickTypeInfoGroup.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<Item> Item::Register;

        auto Item::GetEnumList() -> QStringList& {
            static QStringList EnumList { "TransformOrigin" };
            return EnumList;
        }

        auto Item::MakeEnum(QMetaEnum metaEnum) -> Item* {
            auto prefix = QString(metaEnum.scope()).section("::", 1, 1);
            auto name = QString(metaEnum.name());

            if (GetEnumList().contains(name)) {
                return nullptr;
            }

            auto item = new Item();

            item->m_color = "#B75711";
            item->m_type = "Enum";
            item->m_prefix = prefix;
            item->m_name = name;

            GetEnumList().append(name);

            return item;
        }

        auto Item::MakeClass(QMetaObject metaObject) -> Item* {
            auto item = new Item();

            auto objName = QString(metaObject.className());
            item->m_color = "#319CD3";
            item->m_type = "Class";
            item->m_prefix = objName.section("::", 1, 1);
            item->m_name = objName.section("::", 2, 2);

            return item;
        }

        auto Item::MakeAbstract(QMetaObject metaObject) -> Item* {
            auto item = new Item();

            auto objName = QString(metaObject.className());
            item->m_color = "#6E7582";
            item->m_type = "Abstract";
            item->m_prefix = objName.section("::", 1, 1);
            item->m_name = objName.section("::", 2, 2);

            return item;
        }

        auto Item::matches(const QString& filter) -> bool {
            return this->m_name.contains(filter, Qt::CaseInsensitive);
        }

        auto Item::getName() -> QString {
            return this->m_name;
        }

        auto Item::getPrefix() -> QString {
            return this->m_prefix;
        }

        auto Item::getType() -> QString {
            return this->m_type;
        }

        auto Item::getColor() -> QColor {
            return this->m_color;
        }

        auto Item::add(Group* group) -> void {
            auto index = this->m_groups.count();

            beginInsertRows(QModelIndex(), index, index);
            this->m_groups.append(group);
            endInsertRows();
        }

        auto Item::clear() -> void {
            beginResetModel();
            this->m_groups.clear();
            endResetModel();
        }

        auto Item::roleNames() const -> QHash<int, QByteArray> {
            QHash<int, QByteArray> roles;
            roles[GroupRole] = "group";
            
            return roles;
        }
        
        auto Item::data(const QModelIndex& index, int role) const -> QVariant {
            QVariant var;
            
            if (index.isValid()) {
                if (role == GroupRole) {
                    var.setValue(this->m_groups.at(index.row()));
                }
            }
            
            return var;
        }
        
        auto Item::rowCount(const QModelIndex&) const -> int {
            return this->m_groups.size();
        }
    }
}