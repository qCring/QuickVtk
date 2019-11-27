#include "quickAppMenuItem.hpp"

namespace quick {
    namespace App {

        Qml::Register::Type<MenuItem> MenuItem::Register;
    
        MenuItem::MenuItem(const QString& name) {
            this->m_name = name;
        }

        auto MenuItem::add(MenuItem* item) -> void {
            this->m_items.append(item);
        }
    
        auto MenuItem::setName(const QString& name) -> void {
            this->m_name = name;
            emit this->nameChanged();
        }
    
        auto MenuItem::getName() -> QString {
            return this->m_name;
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
    }
}
