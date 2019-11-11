#include "quickQmlRegister.hpp"

#include "quickTypeInfoSymbol.hpp"
#include "quickTypeInfoList.hpp"

namespace quick {

    namespace Qml {

        namespace Register {

            auto Init() -> void {

                for (auto initializer : Initializers::GetList()) {
                    initializer();
                }

                TypeInfo::List::GetInstance()->init();
            }

            auto Initializers::GetList() -> QList<std::function<void(void)>>& {
                static QList<std::function<void(void)>> List;
                return List;
            }
        }
    }
}
