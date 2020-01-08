#include "quickNotificationItem.hpp"

namespace quick {
    namespace Notification {

        Qml::Register::Type<Item> Item::Register;
    
        Item::Item(const QString& title, const QString& msg, Type type) : m_type(type), m_description(msg) {
        }
    
        auto Item::getDescription() -> QString {
            return this->m_description;
        }
    
        auto Item::getType() -> Type {
            return this->m_type;
        }
    
        auto Item::getTitle() -> QString {
            return this->m_title;
        }
    }
}
