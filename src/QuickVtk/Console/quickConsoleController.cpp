#include "quickConsoleController.hpp"
#include "quickConsoleItem.hpp"

#include "quickMenuController.hpp"

namespace quick {

    namespace Console {

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
    
        auto Controller::getErrorCount() -> int {
            return this->m_errorCount;
        }
    
        auto Controller::getWarningCount() -> int {
            return this->m_warningCount;
        }
    
        auto Controller::setCollapsed(bool collapsed) -> void {
            if (this->m_collapsed != collapsed) {
                this->m_collapsed = collapsed;
                emit this->collapsedChanged();
                
                Menu::Controller::instance->updateViewConsoleMenu(!collapsed);
            }
        }
    
        auto Controller::getCollapsed() -> bool {
            return this->m_collapsed;
        }
    
        void Controller::toggle() {
            this->setCollapsed(!this->m_collapsed);
        }

        void Controller::clear() {
            this->m_items.clear();
            this->m_warningCount = 0;
            this->m_errorCount = 0;
            
            emit this->itemsChanged();
            emit this->errorCountChanged();
            emit this->warningCountChanged();
        }

        auto Controller::addInfoMsg(const QString& msg) -> void {
            this->m_items.append(new Item(QString(msg).remove('\n'), Item::Type::Info));
            
            emit this->itemsChanged();
        }
    
        auto Controller::addDebugMsg(const QString& msg) -> void {
            this->m_items.append(new Item(QString(msg).remove('\n'), Item::Type::Debug));

            emit this->itemsChanged();
        }
    
        auto Controller::addWarningMsg(const QString& msg) -> void {
            this->m_items.append(new Item(QString(msg).remove('\n'), Item::Type::Warning));
            ++this->m_warningCount;
            
            emit this->warningCountChanged();
            emit this->itemsChanged();
        }
    
        auto Controller::addErrorMsg(const QString& msg) -> void {
            this->m_items.append(new Item(QString(msg).remove('\n'), Item::Type::Error));
            ++this->m_errorCount;
            
            emit this->errorCountChanged();
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
