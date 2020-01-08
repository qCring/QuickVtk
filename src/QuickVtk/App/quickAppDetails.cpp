#include "quickAppDetails.hpp"

namespace quick {
    namespace App {

        Details* Details::instance = nullptr;
        Qml::Register::Controller<Details> Details::Register;
    
        auto Details::Create() -> void {
            if (instance) {
                throw std::runtime_error("instance already existing");
            }
            
            instance = new Details();
            instance->showInfo();
        }
    
        auto Details::setCollapsed(bool collapsed) -> void {
            if (this->m_collapsed != collapsed) {
                this->m_collapsed = collapsed;
                emit this->collapsedChanged();
            }
        }
    
        auto Details::getCollapsed() -> bool {
            return this->m_collapsed;
        }
    
        auto Details::getInfo() -> bool {
            return this->m_info;
        }
        
        auto Details::getNotifications() -> bool {
            return this->m_notifications;
        }
        
        auto Details::getTypes() -> bool {
            return this->m_types;
        }
    
        auto Details::setTitle(const QString& title) -> void {
            this->m_title = title;
            emit this->titleChanged();
        }
        
        auto Details::getTitle() -> QString {
            return this->m_title;
        }
    
        void Details::showInfo() {
            this->m_info = true;
            this->m_types = false;
            this->m_notifications = false;
            
            this->setTitle("Information");
            
            emit this->infoChanged();
            emit this->typesChanged();
            emit this->notificationsChanged();
        }
        
        void Details::showNotifications() {
            this->m_info = false;
            this->m_types = false;
            this->m_notifications = true;
            
            this->setTitle("Notifications");
            
            emit this->infoChanged();
            emit this->typesChanged();
            emit this->notificationsChanged();
        }
        
        void Details::showTypes() {
            this->m_info = false;
            this->m_types = true;
            this->m_notifications = false;
            
            this->setTitle("Type List");
            
            emit this->infoChanged();
            emit this->typesChanged();
            emit this->notificationsChanged();
        }
    
        void Details::toggle() {
            this->m_collapsed = !this->m_collapsed;
            emit this->collapsedChanged();
        }
    }
}
