#include "quickAppMenuItem.hpp"

namespace quick {
    namespace App {

        Qml::Register::Type<MenuItem> MenuItem::Register;
    
        MenuItem::MenuItem(const QString& name, Action action) : m_name(name), action(action) {
        }
    
        MenuItem::MenuItem(const QString& name, const QString& icon, Action action) : m_name(name), m_icon(icon), action(action) {
        }

        auto MenuItem::add(MenuItem* item) -> void {
            this->m_items.append(item);
            emit this->itemsChanged();
        }
    
        auto MenuItem::setName(const QString& name) -> void {
            this->m_name = name;
            emit this->nameChanged();
        }
    
        auto MenuItem::getName() -> QString {
            return this->m_name;
        }
    
        auto MenuItem::setIcon(const QString& icon) -> void {
            this->m_icon = icon;
        }
    
        auto MenuItem::getIcon() -> QString {
            return this->m_icon;
        }
    
        auto MenuItem::getItems() -> QQmlListProperty<MenuItem> {
            return QQmlListProperty<MenuItem>(this, 0, &itemsCount, &itemsAt);
        }
    
        auto MenuItem::itemsCount(QQmlListProperty<MenuItem>* list) -> int {
            auto parent = qobject_cast<MenuItem*>(list->object);
            
            if (parent) {
                return parent->m_items.count();
            }
            
            return 0;
        }
    
        auto MenuItem::itemsAt(QQmlListProperty<MenuItem>* list, int index) -> MenuItem* {
            auto parent = qobject_cast<MenuItem*>(list->object);
            
            if (parent) {
                return parent->m_items.at(index);
            }
            
            return nullptr;
        }
    
        auto MenuItem::setData(const QString& data) -> void {
            this->m_data = data;
        }
    
        auto MenuItem::getData() -> QString {
            return this->m_data;
        }
    
        auto MenuItem::removeItems() -> void {
            this->m_items.clear();
            emit this->itemsChanged();
        }
    }
}
