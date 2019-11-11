#include "quickTypeInfoMakeSymbol.hpp"

#include "quickTypeInfoSymbol.hpp"

namespace quick {
    namespace TypeInfo {
        namespace MakeSymbol {

            auto Enum(QMetaEnum metaEnum) -> void {
                Symbol::MakeEnum(metaEnum);
            }
        
            auto Class(QMetaObject metaObject, bool isWrapper) -> void {
                Symbol::MakeClass(metaObject, isWrapper);
            }
        
            auto AbstractClass(QMetaObject metaObject, bool isWrapper) -> void {
                Symbol::MakeAbstractClass(metaObject, isWrapper);
            }
        }
    }
}
