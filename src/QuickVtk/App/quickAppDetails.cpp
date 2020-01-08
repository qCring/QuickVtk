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

        auto Details::getTypes() -> bool {
            return this->m_types;
        }
    
        void Details::showInfo() {
            this->m_info = true;
            this->m_types = false;
            
            emit this->infoChanged();
            emit this->typesChanged();
        }
        
        void Details::showTypes() {
            this->m_info = false;
            this->m_types = true;
            
            emit this->infoChanged();
            emit this->typesChanged();
        }
    
        void Details::toggle() {
            this->m_collapsed = !this->m_collapsed;
            emit this->collapsedChanged();
        }
    }
}
