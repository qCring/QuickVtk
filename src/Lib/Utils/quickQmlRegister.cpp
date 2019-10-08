#include "quickQmlRegister.hpp"

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"

namespace quick {

    namespace Qml {

        namespace Register {

            namespace Symbol {

                namespace Make {

                    auto Enum(QMetaEnum metaEnum) -> void {
                        TypeInfo::Symbol::MakeEnum(metaEnum);
                    }

                    auto Class(QMetaObject metaObject, bool isWrapper) -> void {
                        TypeInfo::Symbol::MakeClass(metaObject, isWrapper);
                    }

                    auto AbstractClass(QMetaObject metaObject, bool isWrapper) -> void {
                        TypeInfo::Symbol::MakeAbstractClass(metaObject, isWrapper);
                    }
                }
            }

            auto Init() -> void {
#ifdef _MSC_VER
                for (auto func : Queue::GetList()) {
                    func();
                }
#endif

                TypeInfo::List::GetInstance()->init();
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
