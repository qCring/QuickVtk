#include "quickConsoleItem.hpp"

namespace quick {
    namespace Console {

        Qml::Register::Type<Item> Item::Register;
    
        Item::Item(const QString& msg, Type type) : m_type(type), m_description(msg) {
            this->m_time = QDateTime::currentDateTime().toString("HH:mm:ss");
            this->m_label = typeToString(type);
        }
    
        auto Item::typeToString(Type type) -> QString {
            switch (type) {
                case Type::Info: return "Info";
                case Type::Debug: return "Debug";
                case Type::Warning: return "Warning";
                case Type::Error: return "Error";
            }
        }
        
        auto Item::getDescription() -> QString {
            return this->m_description;
        }
    
        auto Item::getType() -> Type {
            return this->m_type;
        }
    
        auto Item::getLabel() -> QString {
            return this->m_label;
        }
    
        auto Item::getTime() -> QString {
            return this->m_time;
        }
    }
}
