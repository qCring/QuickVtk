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
            instance->showProperties();
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
    
        auto Details::getProperties() -> bool {
            return this->m_properties;
        }
        
        auto Details::getSettings() -> bool {
            return this->m_settings;
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
    
        void Details::showProperties() {
            this->m_properties = true;
            this->m_settings = false;
            this->m_types = false;
            
            this->setTitle("Properties");
            
            emit this->propertiesChanged();
            emit this->settingsChanged();
            emit this->typesChanged();
        }
        
        void Details::showSettings() {
            this->m_properties = false;
            this->m_settings = true;
            this->m_types = false;
            
            this->setTitle("Settings");
            
            emit this->propertiesChanged();
            emit this->settingsChanged();
            emit this->typesChanged();
        }
        
        void Details::showTypes() {
            this->m_properties = false;
            this->m_settings = false;
            this->m_types = true;
            
            this->setTitle("Type List");
            
            emit this->propertiesChanged();
            emit this->settingsChanged();
            emit this->typesChanged();
        }
    
        void Details::toggle() {
            this->m_collapsed = !this->m_collapsed;
            emit this->collapsedChanged();
        }
    }
}
