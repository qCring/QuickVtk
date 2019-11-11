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

                for (auto func : Queue::GetList()) {
                    func();
                }

                TypeInfo::List::GetInstance()->init();
            }

            auto Queue::GetList()->QList<std::function<void(void)>>& {
                static QList<std::function<void(void)>> List;
                return List;
            }
        }
    }
}
