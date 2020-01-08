#include "quickNotificationController.hpp"
#include "quickNotificationItem.hpp"

namespace quick {

    namespace Notification {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        Controller::Controller() {
            if (instance != nullptr) {
                throw std::runtime_error("instance already existing");
            }
        }

        auto Controller::Create() -> void {
            instance = new Controller();
        }
    
        void Controller::clear() {
            this->m_items.clear();
            emit this->itemsChanged();
        }

        auto Controller::addInfo(const QString& title, const QString& msg) -> void {
            this->m_items.append(new Item(title, msg, Item::Type::Info));
            
            emit this->itemsChanged();
        }
    
        auto Controller::addWarning(const QString& title, const QString& msg) -> void {
            this->m_items.append(new Item(title, msg, Item::Type::Warning));

            emit this->itemsChanged();
        }
    
        auto Controller::addError(const QString& title, const QString& msg) -> void {
            this->m_items.append(new Item(title, msg, Item::Type::Error));

            emit this->itemsChanged();
        }
        
        auto Controller::getItemList() -> QQmlListProperty<Item> {
            return QQmlListProperty<Item>(this, nullptr, &itemCount, &itemAt);
        }
    
        auto Controller::itemCount(QQmlListProperty<Item>* list) -> int {
            auto parent = qobject_cast<Controller*>(list->object);

            if (parent) {
                return parent->m_items.count();
            }

            return 0;
        }

        auto Controller::itemAt(QQmlListProperty<Item>* list, int i) -> Item* {
            auto parent = qobject_cast<Controller*>(list->object);

            if (parent) {
                return parent->m_items.at(i);
            }

            return 0;
        }
    }
}
