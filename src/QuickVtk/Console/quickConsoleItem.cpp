#include "quickConsoleItem.hpp"

namespace quick {
    namespace Console {

        Qml::Register::Type<Item> Item::Register;
    
        Item::Item(const QString& msg, Type type) : m_type(type), m_message(msg) {
            this->m_time = QDateTime::currentDateTime().toString("HH:mm:ss");
        }
    
        auto Item::getMessage() -> QString {
            return this->m_message;
        }
    
        auto Item::getType() -> Type {
            return this->m_type;
        }
    
        auto Item::getTime() -> QString {
            return this->m_time;
        }
    }
}
