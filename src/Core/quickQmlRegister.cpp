#include "quickQmlRegister.hpp"

#include "quickSymbols.hpp"
#include "quickSymbol.hpp"

namespace quick {

    namespace Qml {

        namespace Register {

            namespace MakeSymbol {
                auto Class(QMetaObject metaObject) -> void {
                    Symbols::Add(Symbol::CreateClassSymbol(metaObject));
                }

                auto AbstractClass(QMetaObject metaObject) -> void {
                    Symbols::Add(Symbol::CreateAbstractClassSymbol(metaObject));
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