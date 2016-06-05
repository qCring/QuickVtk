#include "quickTypeInfoList.hpp"
#include "quickTypeInfoItem.hpp"

namespace quick {

    namespace TypeInfo {

        Qml::Register::Type<List> List::Register;

        auto List::GetInstance() -> List* {
            static List* instance = new List();
            return instance;
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
            this->m_items.clear();

            for (auto item : this->m_allItems) {
                if (item->matches(filter)) {
                    this->m_items.append(item);
                }
            }

            this->endResetModel();
        }

        auto List::getFilter() -> QString {
            return this->m_filter;
        }

        auto List::AddEnum(QMetaEnum metaEnum) -> void {
            Add(Item::MakeEnum(metaEnum));
        }

        auto List::AddClass(QMetaObject metaObject) -> void {
            Add(Item::MakeClass(metaObject));
        }

        auto List::AddAbstract(QMetaObject metaObject) -> void {
            Add(Item::MakeAbstract(metaObject));
        }

        auto List::Add(Item* item) -> void {
            if (!item) {
                return;
            }

            auto instance = GetInstance();

            instance->m_items.append(item);
            instance->m_allItems.append(item);
        }

        auto List::clear() -> void {
            beginResetModel();
            this->m_items.clear();
            endResetModel();
        }

        auto List::roleNames() const -> QHash<int, QByteArray> {
            QHash<int, QByteArray> roles;
            roles[ItemRole] = "item";

            return roles;
        }

        auto List::data(const QModelIndex& index, int role) const -> QVariant {
            QVariant var;
            
            if (index.isValid()) {
                if (role == ItemRole) {
                    var.setValue(this->m_items.at(index.row()));
                }
            }
            
            return var;
        }
        
        auto List::rowCount(const QModelIndex&) const -> int {
            return this->m_items.size();
        }
    }
}