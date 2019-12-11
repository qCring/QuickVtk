#include "quickMenuItem.hpp"

namespace quick {
    namespace Menu {

        Qml::Register::Type<Item> Item::Register;
    
        Item::Item(const QString& name, Action action) : m_name(name), action(action) {
        }
    
        Item::Item(const QString& name, const QString& icon, Action action) : m_name(name), m_icon(icon), action(action) {
        }

        auto Item::add(Item* item) -> void {
            this->m_items.append(item);
            emit this->itemsChanged();
        }
    
        auto Item::setName(const QString& name) -> void {
            this->m_name = name;
            emit this->nameChanged();
        }
    
        auto Item::getName() -> QString {
            return this->m_name;
        }
    
        auto Item::setIcon(const QString& icon) -> void {
            this->m_icon = icon;
        }
    
        auto Item::getIcon() -> QString {
            return this->m_icon;
        }
    
        auto Item::getItems() -> QQmlListProperty<Item> {
            return QQmlListProperty<Item>(this, 0, &itemsCount, &itemsAt);
        }
    
        auto Item::itemsCount(QQmlListProperty<Item>* list) -> int {
            auto parent = qobject_cast<Item*>(list->object);
            
            if (parent) {
                return parent->m_items.count();
            }
            
            return 0;
        }
    
        auto Item::itemsAt(QQmlListProperty<Item>* list, int index) -> Item* {
            auto parent = qobject_cast<Item*>(list->object);
            
            if (parent) {
                return parent->m_items.at(index);
            }
            
            return nullptr;
        }
    
        auto Item::setData(const QString& data) -> void {
            this->m_data = data;
        }
    
        auto Item::getData() -> QString {
            return this->m_data;
        }
    
        auto Item::removeItems() -> void {
            this->m_items.clear();
            emit this->itemsChanged();
        }
    
        auto Item::removeItem(const QString& title) -> void {
            for (const auto& item : this->m_items) {
                if (item->getName().compare(title) == 0) {
                    this->m_items.removeOne(item);
                    emit this->itemsChanged();
                    break;
                }
            }
        }
    }
}
