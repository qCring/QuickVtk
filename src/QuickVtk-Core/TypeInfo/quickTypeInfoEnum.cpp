#include "quickTypeInfoEnum.hpp"
#include "quickTypeInfoEnumItem.hpp"

namespace quick {
    namespace TypeInfo {

        Qml::Register::Type<Enum> Enum::Register;

        Enum::Enum() {
        }

        auto Enum::add(EnumItem* item) -> void {
            this->m_enumItems.append(item);
        }
    
        auto Enum::getEnumItemList() -> QQmlListProperty<EnumItem> {
            return QQmlListProperty<EnumItem>(this, this->m_enumItems);
        }
    
        auto Enum::getAllEnumItems() -> QList<EnumItem*> {
            return this->m_enumItems;
        }
    }
}
