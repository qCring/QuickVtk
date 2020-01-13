#include "quickMenuItem.hpp"

namespace quick {
    namespace Menu {

        Qml::Register::Type<Item> Item::Register;

        Item::Item(const QString& label, const QString& icon, Action action, Separator separator) :
        m_label(label), m_icon(icon), m_separator(separator == Separator::On), action(action) {
            
        }
    
        auto Item::Create::SimpleItem(const QString& label, Action action, Separator separator) -> Item* {
            return new Item(label, nullptr, action, separator);
        }
        
        auto Item::Create::IconItem(const QString& label, const QString& icon, Action action, Separator separator) -> Item* {
            return new Item(label, icon, action, separator);
        }

        auto Item::add(Item* item) -> void {
            this->m_items.append(item);
            emit this->itemsChanged();
        }
    
        auto Item::setLabel(const QString& label) -> void {
            this->m_label = label;
            emit this->labelChanged();
        }
    
        auto Item::getLabel() -> QString {
            return this->m_label;
        }
    
        auto Item::setIcon(const QString& icon) -> void {
            this->m_icon = icon;
        }
    
        auto Item::getIcon() -> QString {
            return this->m_icon;
        }
    
        auto Item::getSeparator() -> bool {
            return this->m_separator;
        }
    
        auto Item::getItemList() -> QQmlListProperty<Item> {
            return QQmlListProperty<Item>(this, 0, &itemsCount, &itemsAt);
        }
    
        auto Item::getItems() -> QList<Item*> {
            return this->m_items;
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
                if (item->getLabel().compare(title) == 0) {
                    this->m_items.removeOne(item);
                    emit this->itemsChanged();
                    break;
                }
            }
        }
    
        auto Item::isEmpty() -> bool {
            return this->m_items.isEmpty();
        }
    
        auto Item::setEnabled(bool enabled) -> void {
            if (this->m_enabled != enabled) {
                this->m_enabled = enabled;
                emit this->enabledChanged();
            }
        }
    
        auto Item::getEnabled() -> bool {
            return this->m_enabled;
        }
    }
}
