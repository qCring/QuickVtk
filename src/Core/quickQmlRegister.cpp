#include "quickQmlRegister.hpp"

#include "quickTypeInfoSymbol.hpp"

namespace quick {

    namespace Qml {

        namespace Register {

            namespace MakeSymbol {
                auto Enum(QMetaEnum metaEnum) -> void {
                    TypeInfo::Symbol::MakeEnum(metaEnum);
                }

                auto Class(QMetaObject metaObject) -> void {
                    TypeInfo::Symbol::MakeClass(metaObject);
                }

                auto AbstractClass(QMetaObject metaObject) -> void {
                    TypeInfo::Symbol::MakeAbstractClass(metaObject);
                }
            }

            auto Init() -> void {
#ifdef _MSC_VER
                for (auto func : Queue::GetList()) {
                    func();
                }
#endif
            }

#ifdef _MSC_VER
            auto Queue::GetList()->QList<std::function<void(void)>>& {
                static QList<std::function<void(void)>> List;
                return List;
            }
#endif
        }
    }
}