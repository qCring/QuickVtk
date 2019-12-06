#include "quickConsoleController.hpp"
#include "quickConsoleItem.hpp"

namespace quick {

    namespace Console {

        Controller* Controller::instance = nullptr;
        Qml::Register::Controller<Controller> Controller::Register;

        Controller::Controller() {
        }

        auto Controller::Create() -> void {
            instance = new Controller();
        }

        auto Controller::GetInstance() -> Controller* {
            return instance;
        }

        void Controller::clear() {
            this->m_items.clear();
            emit this->itemsChanged();
        }

        auto Controller::addInfoMsg(const QString& msg) -> void {
            this->m_items.append(new Item(msg, Item::Type::Info));
            
            emit this->itemsChanged();
        }
    
        auto Controller::addDebugMsg(const QString& msg) -> void {
            this->m_items.append(new Item(msg, Item::Type::Debug));

            emit this->itemsChanged();
        }
    
        auto Controller::addWarningMsg(const QString& msg) -> void {
            this->m_items.append(new Item(msg, Item::Type::Warning));
            
            emit this->itemsChanged();
        }
    
        auto Controller::addErrorMsg(const QString& msg) -> void {
            this->m_items.append(new Item(msg, Item::Type::Error));
            
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
